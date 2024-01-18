#ifndef EDGE_DETECTOR_H
#define EDGE_DETECTOR_H

#include "ImageMatrix.h"
#include "Convolution.h"
#include <vector>

class EdgeDetector {
public:
    EdgeDetector();
    ~EdgeDetector();

    std::vector<std::pair<int, int>> detectEdges(const ImageMatrix& input_image);

private:
    // add your private member variables and functions
    double** sobel_operator_x;
    double** sobel_operator_y;
    int sobel_operator_height;
    int sobel_operator_width;
};

#endif // EDGE_DETECTOR_H


