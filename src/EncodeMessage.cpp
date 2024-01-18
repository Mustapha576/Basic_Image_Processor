#include "EncodeMessage.h"
#include <cmath>
#include <iostream>
#include <bitset>


// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {

}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions) {
    int length = message.length();
    std::string encodingProcess;
    std::string binaryString;

    int t1 = 0;
    int t2 = 1;
    int next = 0;

    for(int i = 0; i < length; i++){
        char value = message[i];
        int asciiValue = static_cast<int>(value);
        if(isPrime(i)){
            int fibIndex = i;
            for(int j = 2; j <= fibIndex ; ++j) //loop starts from 2 because 0 and 1 are already printed
            {
                next = t1 + t2;
                t1 = t2;
                t2 = next;
            }
            int newValue = asciiValue + next;

            if(newValue <= 32){
                newValue += 33;
            }
            else if(newValue >= 127){
                newValue = 126;
            }

            t1 = 0;
            t2 = 1;
            next = 0;

            char character = static_cast<char>(newValue);
            encodingProcess += character;
        }
        else{
            if(asciiValue <= 32){
                asciiValue += 33;
            }
            else if(asciiValue >= 127){
                asciiValue = 126;
            }
            char character = static_cast<char>(asciiValue);
            encodingProcess += character;
        }
    }

    int encodingProcessLength = encodingProcess.length();
    std::string shifted;

    if(encodingProcessLength % 2 == 1){
        shifted = encodingProcess.substr(length / 2 + 1) + encodingProcess.substr(0, length / 2 + 1);
    }
    else if (encodingProcessLength % 2 == 0){
        shifted = encodingProcess.substr(length / 2 ) + encodingProcess.substr(0, length / 2);
    }

    std::cout << shifted << std::endl;

    // 100001000100111100010(1 to 0)000(1 to 0)
    int shifted_size = shifted.length();
    for(int i = 0; i < shifted_size; i++){
        std::bitset<7> binary(static_cast<int>(shifted[i]));
        binaryString += binary.to_string();
    }

    std::cout << binaryString << std::endl;

    int binaryStringValues = 0;

    encodedImage = img;

    for (int i = 0; i < positions.size(); i++) {
        if(i < binaryString.size()){
            double pixelValue = img.get_data(positions[i].first, positions[i].second);
            int intPixelValue = static_cast<int>(pixelValue);
            std::string stringBinaryString(1, binaryString[binaryStringValues]);

            //int lsb = (char(shifted[i / 7]) >> i) & 1;
            int newLSB = std::stoi(stringBinaryString, nullptr, 2);
            intPixelValue &= ~1;
            intPixelValue |= newLSB;
            encodedImage.get_data()[positions[i].first][positions[i].second] = intPixelValue;
            binaryStringValues++;
        }
    }
    return encodedImage;
}

bool EncodeMessage::isPrime(int num) const {
    if (num < 2) {
        return false;
    }

    for (int i = 2; i <= sqrt(num); ++i) {
        if (num % i == 0) {
            return false;  // If the number is divisible by i, it's not prime
        }
    }
    return true;

}

