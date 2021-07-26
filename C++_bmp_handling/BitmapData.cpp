
#include <iostream>
#include <fstream>
#include "BitmapData.h"
#include "BitmapFileAddresses.h"

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
void BitmapData::LoadImage(const char* path)
{
    std::ifstream in(path, std::ios::binary);

    char c;

    int iLineNumber = 0;
    unsigned int iImageDataIndex = 0;
    unsigned int iFileByteSize = 0;


    while (in)
    {
        if(false) // Debug! Print all bytes
        {
            in.get(c);
            unsigned char c2 = reinterpret_cast<unsigned char&>(c);
            unsigned int value = int(c2);
            std::cout << iLineNumber << ": " << std::hex << value << std::dec << "\n";
            iLineNumber++;
        }
        else
        {
            //printf("iLineNumber = %d\n", iLineNumber);

            if(iLineNumber == ADDR_FILE_TYPE) // File type
            {
                unsigned int cTot = 0;
                for(int iByte = 0; iByte < ADDR_FILE_TYPE_BYTES; iByte++)
                {
                    in.get(c);
                    unsigned char c2 = reinterpret_cast<unsigned char&>(c);
                    unsigned int value = int(c2);
                    cTot = (cTot<<8*iByte) + value;
                    iLineNumber++;
                }
                m_iFileType = cTot;
            }
            else if(iLineNumber == ADDR_FILE_BYTESIZE) // File size
            {
                unsigned int cTot = 0;
                for(int iByte = 0; iByte < ADDR_FILE_BYTESIZE_BYTES; iByte++)
                {
                    in.get(c);
                    unsigned char c2 = reinterpret_cast<unsigned char&>(c);
                    unsigned int value = int(c2);
                    int increment = value<<(8*iByte);
                    cTot = cTot + increment;
                    iLineNumber++;
                }
                m_iFileSize = cTot;
            }
            else if(iLineNumber == ADDR_DATA_OFFSET) // Image data address
            {
                unsigned int cTot = 0;
                for(int iByte = 0; iByte < ADDR_DATA_OFFSET_BYTES; iByte++)
                {
                    in.get(c);
                    unsigned char c2 = reinterpret_cast<unsigned char&>(c);
                    unsigned int value = int(c2);
                    int increment = value<<(8*iByte);
                    cTot = cTot + increment;
                    iLineNumber++;
                }
                m_iImageDataAddress = cTot;
            }
            else // Flush all non-defined bytes in file
            {
                in.get(c);
                iLineNumber++;
            }
        }
    }
}



/***************************************************************************
GetFileSize()
***************************************************************************/
int BitmapData::GetFileSize()
{
    return m_iFileSize;
}

/***************************************************************************
GetFileSize()
***************************************************************************/
unsigned int BitmapData::GetFileType()
{
    return m_iFileType;
}

/***************************************************************************
GetImageDataAddress()
***************************************************************************/
unsigned int BitmapData::GetImageDataAddress()
{
    return m_iImageDataAddress;
}



