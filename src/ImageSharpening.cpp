#include <iostream>
#include "ImageSharpening.h"

// Default constructor
ImageSharpening::ImageSharpening() {
    this->kernel_height = 3;
    this->kernel_width = 3;

    this->blurring_kernel = new double*[kernel_height];
    for(int i = 0; i < kernel_height; i++){
        blurring_kernel[i] = new double[kernel_width];
        for(int j = 0; j < kernel_width; j++){
            blurring_kernel[i][j] = 1.0 / 9.0;
        }
    }

}

ImageSharpening::~ImageSharpening(){
    if(blurring_kernel != nullptr){
        for(int i = 0; i < kernel_height; i++){
            delete[] blurring_kernel[i];
        }
        delete[] blurring_kernel;
        //blurring_kernel = nullptr;
    }
}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    Convolution blurring(blurring_kernel, kernel_height, kernel_width, 1, true);
    ImageMatrix blurred_image = blurring.convolve(input_image);
    for(int i = 0; i < blurred_image.get_height(); i++){
        for(int j = 0; j < blurred_image.get_width(); j++){
            if(input_image.get_data()[i][j] + k * (input_image.get_data()[i][j] - blurred_image.get_data()[i][j]) <= 0 ){
                blurred_image.get_data()[i][j] = 0;
            }
            else if(input_image.get_data()[i][j] + k * (input_image.get_data()[i][j] - blurred_image.get_data()[i][j]) >= 255 ){
                blurred_image.get_data()[i][j] = 255;
            }
            else{
                blurred_image.get_data()[i][j] = input_image.get_data()[i][j] + k * (input_image.get_data()[i][j] - blurred_image.get_data()[i][j]);
            }
        }
    }
    /*
    for(int a = 0; a < blurred_image.get_height(); a++){
        for(int b = 0; b < blurred_image.get_width(); b++){
            std::cout << blurred_image.get_data()[a][b] << " ";
        }
        std::cout << std::endl;
    }
    */

    return blurred_image;
}
