// DecodeMessage.cpp

#include "DecodeMessage.h"
#include "ImageSharpening.h"
#include <iostream>
#include <vector>
#include <utility>
#include <bitset>

using namespace std;

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}


std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    string message_to_binary;
    string message;

    for (const auto &pair : edgePixels) {
        int x = pair.first;
        int y = pair.second;
        if (x >= 0 && x < image.get_height() && y >= 0 && y < image.get_width()) {
            double value = image.get_data()[x][y];
            int intValue = static_cast<int>(value);
            message_to_binary += to_string(intValue & 1);
        }
    }

    int length = message_to_binary.length();
    if((length % 7) != 0){
        for(int i = 0; i < (7 - (length % 7)) ; i++){
            message_to_binary = "0" + message_to_binary;
        }
    }

    int message_size = message_to_binary.length();

    for(int i = 0; i < message_size; i += 7){
        string seven_bits = message_to_binary.substr(i, 7);
        bitset<7> bits(seven_bits);
        unsigned long decimalValue = bits.to_ulong();
        int asciiValue = static_cast<int>(decimalValue);
        if(asciiValue <= 32){
            asciiValue += 33;
        }

        else if(asciiValue >= 127){
            asciiValue = 126;
        }

        message += static_cast<char>(asciiValue);
    }
    return message;

}

