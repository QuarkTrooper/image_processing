
#include <iostream>
#include <fstream>
#include "BitmapData.h"

#define DEBUG_PRINTS

/***************************************************************************
Constructor
***************************************************************************/
BitmapData::BitmapData()
{
}

/***************************************************************************
Destructor
***************************************************************************/
BitmapData::~BitmapData()
{
}

/***************************************************************************
LoadImage()

Takes a path to a bitmap file which is parsed and the data is saved into a
BitmapData object.
***************************************************************************/
BitmapData::LoadImage(const char* path)
{
    std::ifstream in(path, std::ios::binary);

#ifdef DEBUG_PRINTS
    std::cout << "\n\n";
    std::cout << "====================================\n";
    std::cout << "HEX\t\tDEC\n";
    std::cout << "====================================\n";
#endif

    short unsigned int iLineNumber = 0;
    unsigned int iImageDataIndex = 0;
#ifdef DEBUG_PRINTS
    std::cout << std::uppercase;
#endif
    while (in)
    {
        // Extract current byte
        char c;
        in.get(c);
        unsigned char c2 = reinterpret_cast<unsigned char&>(c);
        unsigned int value = int(c2);

        // Save value of byte accordingly
        if(iLineNumber == 10)
        {
            iImageDataIndex = value;
        }
        if(iLineNumber >= iImageDataIndex)
        {

        }
        else
        {
            if (in)
            {
#ifdef DEBUG_PRINTS
                std::cout << iLineNumber << ": " << "0x" << std::hex << value << std::dec << "\t\t" << value << "\n";
#endif
            }
        }
        iLineNumber++;
    }
#ifdef DEBUG_PRINTS
    std::cout << std::nouppercase;
    std::cout << "\n\n";
#endif

    // Terminate
    return 0;
}




