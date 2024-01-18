#include <iostream>
#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    std::vector<std::pair<int, int>> edgePixels;
    ImageMatrix sharpening;
    EdgeDetector edgeDetector;
    ImageSharpening imageSharpening;
    DecodeMessage decodeMessage;

    sharpening = imageSharpening.sharpen(img, 2);
    edgePixels = edgeDetector.detectEdges(sharpening);
    std::string message = decodeMessage.decodeFromImage(sharpening, edgePixels);

    return message;
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    std::vector<std::pair<int, int>> edgePixels;
    ImageMatrix sharpening;
    EdgeDetector edgeDetector;
    ImageSharpening imageSharpening;
    EncodeMessage encodeMessage;
    ImageMatrix copyImage = img;

    sharpening = imageSharpening.sharpen(img, 2);
    edgePixels = edgeDetector.detectEdges(sharpening);
    ImageMatrix imageMatrix = encodeMessage.encodeMessageToImage(copyImage, message, edgePixels);

    return imageMatrix;

}
