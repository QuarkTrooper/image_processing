
#include <iostream>
#include <fstream>
#include "BitmapData.h"

int main(int argc, const char *argv[])
{
    // Main input sanity check
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << "white_test_image.bmp\n";
        return 1;
    }

    // Load file data
    BitmapData fileData;
    const char* sPathString = argv[1];
    fileData.LoadImage(sPathString);

    std::cout << "File size: " << fileData.GetFileSize() << "\n";
    std::cout << "File type: " << std::uppercase << std::hex << fileData.GetFileType() << std::dec << std::nouppercase << "\n";
    std::cout << "Image data address: " << std::uppercase << std::hex << fileData.GetImageDataAddress() << std::dec << std::nouppercase << "\n";

    // Terminate
    return 0;
}