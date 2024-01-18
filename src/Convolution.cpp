#include <iostream>

#include "Convolution.h"

// Default constructor
Convolution::Convolution() : kh(3), kw(3), stride_val(1), pad(true){
    customKernel = new double*[kh];
    for (int i = 0; i < kh; ++i) {
        customKernel[i] = new double[kw]; // Initialize elements to default values
    }
}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad){
    this->kh = kh;
    this->kw = kw;
    this->stride_val = stride_val;
    this->pad = pad;

    this->customKernel = new double*[kh];
    for (int i = 0; i < kh; ++i) {
        this->customKernel[i] = new double[kw];
        for (int j = 0; j < kw; ++j) {
            this->customKernel[i][j] = customKernel[i][j];
        }
    }
}

// Destructor
Convolution::~Convolution() {
    if (customKernel != nullptr) {
        for (int i = 0; i < kh; ++i) {
            delete[] customKernel[i];
        }
        delete[] customKernel;
        //customKernel = nullptr;
    }
}

// Copy constructor
Convolution::Convolution(const Convolution &other){
    kh = other.kh;
    kw = other.kw;
    stride_val = other.stride_val;
    pad = other.pad;

    // Allocate memory for the kernel matrix and perform deep copy
    customKernel = new double*[kh];
    for (int i = 0; i < kh; ++i) {
        customKernel[i] = new double[kw];
    }

    // Copy data from the object 'other' to data
    for (int i = 0; i < kh; ++i) {
        for (int j = 0; j < kw; ++j) {
            customKernel[i][j] = other.customKernel[i][j];
        }
    }
}


// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this == &other){
        return *this;
    }

    else {
        // Deallocate existing kernel memory
        for (int i = 0; i < kh; ++i) {
            delete[] customKernel[i];
        }
        delete[] customKernel;

        // Copy values and allocate new memory for the kernel matrix
        kh = other.kh;
        kw = other.kw;
        stride_val = other.stride_val;
        pad = other.pad;

        customKernel = new double*[kh];
        for (int i = 0; i < kh; ++i) {
            customKernel[i] = new double[kw];
            for (int j = 0; j < kw; ++j) {
                customKernel[i][j] = other.customKernel[i][j];
            }
        }
        return *this;
    }

}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.

ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    if(pad == 0){
        if(stride_val == 1){
            int resultHeight = ((input_image.get_height() - get_kernel_height() + 2 * get_kernel_pad()) / get_kernel_stride()) + 1;
            int resultWidth = ((input_image.get_height() - get_kernel_height() + 2 * get_kernel_pad()) / get_kernel_stride()) + 1;

            // Create a new matrix for the result
            ImageMatrix result(resultHeight, resultWidth);

            for (int i = 0; i < resultHeight; ++i) {
                for (int j = 0; j < resultWidth; ++j) {
                    // Calculate the element-wise product and sum for each position (i, j)
                    double sum = 0.0;
                    for (int k = 0; k < get_kernel_height(); ++k) {
                        for (int l = 0; l < get_kernel_width(); ++l) {
                            sum += input_image.get_data()[i + k][j + l] * get_kernel()[k][l];
                        }
                    }
                    result.get_data()[i][j] = sum;
                }
            }

            return result;
        }
        else{
            int resultHeight = ((input_image.get_height() - get_kernel_height() + 2 * get_kernel_pad()) / get_kernel_stride()) + 1;
            int resultWidth = ((input_image.get_height() - get_kernel_height() + 2 * get_kernel_pad()) / get_kernel_stride()) + 1;

            // Create a new matrix for the result
            ImageMatrix result(resultHeight, resultWidth);


            for (int i = 0; i <= resultHeight; i += 2) {
                for (int j = 0; j <= resultWidth; j += 2) {
                    // Calculate the element-wise product and sum for each position (i, j)
                    double sum = 0.0;
                    for (int k = 0; k < get_kernel_height(); ++k) {
                        for (int l = 0; l < get_kernel_width(); ++l) {
                            sum += input_image.get_data()[i + k][j + l] * get_kernel()[k][l];
                        }
                    }
                    result.get_data()[i/2][j/2] = sum;
                }
            }
             return result;
        }
    }

    else if(pad == 1){
        if(stride_val == 1){
            int resultHeight = ((input_image.get_height() - get_kernel_height() + 2 * get_kernel_pad()) / get_kernel_stride()) + 1;
            int resultWidth = ((input_image.get_height() - get_kernel_height() + 2 * get_kernel_pad()) / get_kernel_stride()) + 1;
            // Create a new matrix for the result
            ImageMatrix result(resultHeight, resultWidth);

            ImageMatrix with_padding(input_image.get_height() + 2, input_image.get_width() + 2);

            int padding_size = (with_padding.get_height() - input_image.get_height()) / 2;
            for (int i = 0; i < with_padding.get_height(); ++i) {
                with_padding.get_data()[i] = new double[with_padding.get_width()];
                for (int j = 0; j < with_padding.get_width(); ++j) {
                    if (i < padding_size || i >= (input_image.get_height() + padding_size) ||
                        j < padding_size || j >= (input_image.get_width() + padding_size)) {
                        // Fill the padding area with zeros
                        with_padding.get_data()[i][j] = 0.0;
                    } else {
                        // Copy the input image into the center of the padded matrix
                        with_padding.get_data()[i][j] = input_image.get_data()[i - padding_size][j - padding_size];
                    }
                }
            }

            for (int i = 0; i < resultHeight; ++i) {
                for (int j = 0; j < resultWidth; ++j) {
                    // Calculate the element-wise product and sum for each position (i, j)
                    double sum = 0.0;
                    for (int k = 0; k < get_kernel_height(); ++k) {
                        for (int l = 0; l < get_kernel_width(); ++l) {
                            sum += with_padding.get_data()[i + k][j + l] * get_kernel()[k][l];
                        }
                    }
                    result.get_data()[i][j] = sum;
                }
            }

            return result;
        }
        else{
            int resultHeight = ((input_image.get_height() - get_kernel_height() + 2 * get_kernel_pad()) / get_kernel_stride() + 1);
            int resultWidth = ((input_image.get_width() - get_kernel_width() + 2 * get_kernel_pad()) / get_kernel_stride() + 1);

            // Create a new matrix for the result
            ImageMatrix result(resultHeight, resultWidth);

            ImageMatrix with_padding(input_image.get_height() + 2, input_image.get_width()  + 2);

            int padding_size = (with_padding.get_height() - input_image.get_height()) / 2;
            for (int i = 0; i < with_padding.get_height(); ++i) {
                with_padding.get_data()[i] = new double[with_padding.get_width()];
                for (int j = 0; j < with_padding.get_width(); ++j) {
                    if (i < padding_size || i >= (input_image.get_height() + padding_size) ||
                        j < padding_size || j >= (input_image.get_width() + padding_size)) {
                        // Fill the padding area with zeros
                        with_padding.get_data()[i][j] = 0.0;
                    } else {
                        // Copy the input image into the center of the padded matrix
                        with_padding.get_data()[i][j] = input_image.get_data()[i - padding_size][j - padding_size];
                    }
                }
            }

            for (int i = 0; i <= resultHeight + 1; i += 2) {
                for (int j = 0; j <= resultWidth + 1; j += 2) {
                    // Calculate the element-wise product and sum for each position (i, j)
                    double sum = 0.0;
                    for (int k = 0; k < get_kernel_height(); ++k) {
                        for (int l = 0; l < get_kernel_width(); ++l) {
                            sum += with_padding.get_data()[i + k][j + l] * get_kernel()[k][l];
                        }
                    }
                    result.get_data()[i/2][j/2] = sum;
                }
            }

            return result;
        }
    }
}


double** Convolution::get_kernel() const{
    return customKernel;
}

int Convolution::get_kernel_height() const{
    return kh;
}

int Convolution::get_kernel_width() const{
    return kw;
}

int Convolution::get_kernel_stride() const{
    return stride_val;
}

bool Convolution::get_kernel_pad() const {
    return pad;
}
