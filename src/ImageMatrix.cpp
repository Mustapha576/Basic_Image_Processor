#include "ImageMatrix.h"
#include <iostream>


// Default constructor
ImageMatrix::ImageMatrix() : height(1), width(1), data(nullptr){
    data = new double*[height];
    for(int i = 0; i < height; i++){
        data[i] = new double[width];
    }
}


// Parameterized constructor for creating a blank image of given size
ImageMatrix::ImageMatrix(int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {
    data = new double*[imgHeight]; //this
    for (int i = 0; i < imgHeight; ++i) {
        data[i] = new double[imgWidth]; //this
        for(int j = 0; j < imgWidth; j++){
            data[i][j] = 0; //this
        }
    }

}

// Parameterized constructor for loading image from file. PROVIDED FOR YOUR CONVENIENCE
ImageMatrix::ImageMatrix(const std::string &filepath) {
    // Create an ImageLoader object and load the image
    ImageLoader imageLoader(filepath);

    // Get the dimensions of the loaded image
    height = imageLoader.getHeight();
    width = imageLoader.getWidth();

    // Allocate memory for the matrix
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }

    // Copy data from imageLoader to data
    double** imageData = imageLoader.getImageData();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = imageData[i][j];
        }
    }
}



// Destructor
ImageMatrix::~ImageMatrix() {
    if (data != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] data[i];
        }
        delete[] data;
        //data = nullptr;
    }
}

// Parameterized constructor - direct initialization with 2D matrix
ImageMatrix::ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth){
    //this->data = const_cast<double **>(inputMatrix);
    this->height = imgHeight;
    this->width = imgWidth;
    data = new double*[imgHeight];
    for (int i = 0; i < imgHeight; ++i) {
        data[i] = new double[imgWidth];
        for (int j = 0; j < imgWidth; ++j) {
            data[i][j] = inputMatrix[i][j];
        }
    }
}


// Copy constructor
ImageMatrix::ImageMatrix(const ImageMatrix &other) {
    // Copy dimensions
    height = other.height;
    width = other.width;

    // Allocate memory for the new matrix
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

// Copy assignment operator
ImageMatrix& ImageMatrix::operator=(const ImageMatrix &other) {
    if (this != &other) { // Check for self-assignment
        // Free the existing memory
        for (int i = 0; i < height; ++i) {
            delete[] data[i];
        }
        delete[] data;

        // Copy dimensions
        height = other.height;
        width = other.width;

        // Allocate new memory for the current object
        data = new double*[height];
        for (int i = 0; i < height; ++i) {
            data[i] = new double[width];
            for (int j = 0; j < width; ++j) {
                // Copy data from 'other' object to the current object
                data[i][j] = other.data[i][j];
            }
        }
    }
    return *this;
}



// Overloaded operators

// Overloaded operator + to add two matrices
ImageMatrix ImageMatrix::operator+(const ImageMatrix &other) const {
    ImageMatrix result(height, width);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }

    return result;
}

// Overloaded operator - to subtract two matrices
ImageMatrix ImageMatrix::operator-(const ImageMatrix &other) const {
    ImageMatrix result(height, width);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }

    return result;
}

// Overloaded operator * to multiply a matrix with a scalar
ImageMatrix ImageMatrix::operator*(const double &scalar) const {
    ImageMatrix result(height, width);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }

    return result;
}


// Getter function to access the data in the matrix
double** ImageMatrix::get_data() const {
    return data;
}

int ImageMatrix::get_height() const{
    return height;
};

int ImageMatrix::get_width() const{
    return width;
};

// Getter function to access the data at the index (i, j)
double ImageMatrix::get_data(int i, int j) const {
    if (i >= 0 && i < height && j >= 0 && j < width) {
        return data[i][j];  // Return the value at index (i, j)
    } else {
        // Return a default value or handle out-of-bounds access as needed
        // For example, returning 0 might not be suitable in all cases
        // Modify this based on your specific use case
        return 0.0;
    }
}

