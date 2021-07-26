
#include <iostream>
#include <fstream>
#include "BitmapData.h"

int main(int argc, const char *argv[])
{
    //if (argc < 2) {
    //    std::cerr << "Usage: " << argv[0] << "white_test_image.bmp\n";
    //    return 1;
    //}
    //std::ifstream in(argv[1], std::ios::binary);
    //std::cout << "\n\n";
    //std::cout << "====================================\n";
    //std::cout << "HEX\t\tDEC\n";
    //std::cout << "====================================\n";
//
    //short unsigned int iLineNumber = 0;
    //unsigned int iImageDataIndex = 0;
    //std::cout << std::uppercase;
    //while (in)
    //{
    //    char c;
    //    in.get(c);
    //    unsigned char c2 = reinterpret_cast<unsigned char&>(c);
    //    //unsigned char c2 = static_cast<unsigned char&>(c);
    //    if(iLineNumber == 10)
    //    {
    //        iImageDataIndex = int(c2);
    //    }
    //    if(iLineNumber >= iImageDataIndex)
    //    {
//
    //    }
    //    else
    //    {
    //        if (in)
    //        {
    //            std::cout << iLineNumber << ": " << "0x" << std::hex << int(c2) << std::dec << "\t\t" << int(c2) << "\n";
    //        }
    //    }
    //    iLineNumber++;
    //}
    //std::cout << std::nouppercase;
    //std::cout << "\n\n";

    BitmapData fileData;
    //std::string sPathString = "white_test_image.bmp";
    const char* sPathString = argv[1];

    fileData.LoadImage(sPathString);

    return 0;
}