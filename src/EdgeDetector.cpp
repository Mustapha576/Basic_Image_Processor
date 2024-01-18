// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>
#include "iostream"
#include "EdgeDetector.h"
#include <cmath>

// Default constructor
EdgeDetector::EdgeDetector() {
    this->sobel_operator_height = 3;
    this->sobel_operator_width = 3;
    this->sobel_operator_x = new double*[sobel_operator_height];
    sobel_operator_x[0] = new double[3]{-1.0, 0.0, 1.0};
    sobel_operator_x[1] = new double[3]{-2.0, 0.0, 2.0};
    sobel_operator_x[2] = new double[3]{-1.0, 0.0, 1.0};

    this->sobel_operator_y = new double*[sobel_operator_height];
    sobel_operator_y[0] = new double[3]{-1.0, -2.0, -1.0};
    sobel_operator_y[1] = new double[3]{0.0, 0.0, 0.0};
    sobel_operator_y[2] = new double[3]{1.0, 2.0, 1.0};
}

// Destructor
EdgeDetector::~EdgeDetector() {
    if(sobel_operator_x != nullptr){
        for(int i = 0; i < sobel_operator_height; i++){
            delete[] sobel_operator_x[i];
        }
        delete[] sobel_operator_x;
        //sobel_operator_x = nullptr;
    }
    if(sobel_operator_y != nullptr){
        for(int i = 0; i < sobel_operator_height; i++){
            delete[] sobel_operator_y[i];
        }
        delete[] sobel_operator_y;
        //sobel_operator_y = nullptr;
    }
}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {

    Convolution edge_detection_for_y(sobel_operator_y, sobel_operator_height, sobel_operator_width, 1, true);
    ImageMatrix TemporaryIy = edge_detection_for_y.convolve(input_image);

    Convolution edge_detection_for_x(sobel_operator_x, sobel_operator_height, sobel_operator_width, 1, true);
    ImageMatrix TemporaryIx = edge_detection_for_x.convolve(input_image);

    ImageMatrix blank_image(TemporaryIx.get_height(), TemporaryIx.get_width());

    double value_addition = 0;

    for(int i = 0; i < blank_image.get_height(); i++){
        for(int j = 0; j < blank_image.get_width(); j++){
            blank_image.get_data()[i][j] = sqrt((pow(TemporaryIx.get_data()[i][j], 2) + pow(TemporaryIy.get_data()[i][j], 2)));
            value_addition += blank_image.get_data()[i][j];
        }
    }

    std::vector<std::pair<int, int>> GettingEdges;
    double threshold_value = value_addition / (blank_image.get_height() * blank_image.get_width());
    for(int i = 0; i < blank_image.get_height(); i++){
        for(int j = 0; j < blank_image.get_width(); j++){
            if(blank_image.get_data()[i][j] > threshold_value){
                GettingEdges.emplace_back(i, j);
            }
        }
    }

    return GettingEdges;

}

