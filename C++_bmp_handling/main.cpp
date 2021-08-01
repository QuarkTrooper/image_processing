
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

    fileData.PrintBitmapInfo();
    //fileData.PrintPixelArray(eBLUE); // blue
    //fileData.PrintPixelArray(eGREEN); // green
    //fileData.PrintPixelArray(eRED); // red

    // Terminate
    return 0;
}