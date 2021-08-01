
#include <iostream>
#include <iomanip>
#include <fstream>
#include "BitmapData.h"

#define DEBUG_PRINTS

/***************************************************************************
Constructor
***************************************************************************/
BitmapData::BitmapData()
{
    m_ImageData = nullptr;
    m_iFileSize = 0;
    m_iFileType = 0;
    m_iImageDataAddress = 0;
    m_iInfoHeaderSize = 0;
    m_eInfoHeaderType = NOTSPECIFIED;
}

/***************************************************************************
Destructor
***************************************************************************/
BitmapData::~BitmapData()
{
    delete m_ImageData;
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
        if(false) // If true debug (I.e. just print all bytes and do not save)
        {
            in.get(c);
            unsigned char c2 = reinterpret_cast<unsigned char&>(c);
            unsigned int value = int(c2);
            if(false) // if true, print values as hex, otherwise as dec
            {
                std::cout << iLineNumber << ": " << std::hex << value << std::dec << "\n";
            }
            else
            {
                std::cout << iLineNumber << ": " << value << "\n";
            }
            iLineNumber++;
        }
        else
        {
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
            else if(iLineNumber == ADDR_HEADER_TYPE) // Header type
            {
                unsigned int cTot = 0;
                for(int iByte = 0; iByte < ADDR_HEADER_TYPE_BYTES; iByte++)
                {
                    in.get(c);
                    unsigned char c2 = reinterpret_cast<unsigned char&>(c);
                    unsigned int value = int(c2);
                    int increment = value<<(8*iByte);
                    cTot = cTot + increment;
                    iLineNumber++;
                }
                m_iInfoHeaderSize = cTot;
                SetInfoHeaderType();
            }
            else if(iLineNumber == GetImageWidthAddress()) // Image width
            {
                unsigned int cTot = 0;
                for(int iByte = 0; iByte < 4; iByte++) // Need to store that it's supposed to be 4 bytes somewhere better
                {
                    in.get(c);
                    unsigned char c2 = reinterpret_cast<unsigned char&>(c);
                    unsigned int value = int(c2);
                    int increment = value<<(8*iByte);
                    cTot = cTot + increment;
                    iLineNumber++;
                }
                m_iImageWidth = cTot;
            }
            else if(iLineNumber == GetImageHeightAddress()) // Image width
            {
                unsigned int cTot = 0;
                for(int iByte = 0; iByte < 4; iByte++) // Need to store that it's supposed to be 4 bytes somewhere better
                {
                    in.get(c);
                    unsigned char c2 = reinterpret_cast<unsigned char&>(c);
                    unsigned int value = int(c2);
                    int increment = value<<(8*iByte);
                    cTot = cTot + increment;
                    iLineNumber++;
                }
                m_iImageHeight = cTot;
            }
            else if(iLineNumber == GetImageColorDepthAddress()) // Image colorDepth
            {
                unsigned int cTot = 0;
                for(int iByte = 0; iByte < 2; iByte++) // Need to store that it's supposed to be 2 bytes somewhere better
                {
                    in.get(c);
                    unsigned char c2 = reinterpret_cast<unsigned char&>(c);
                    unsigned int value = int(c2);
                    int increment = value<<(8*iByte);
                    cTot = cTot + increment;
                    iLineNumber++;
                }
                m_iImageColorDepth = cTot;
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
            else if(iLineNumber == GetImageDataAddress()) // Pixel data
            {
                m_ImageData = new PixelArray(m_iImageHeight, m_iImageWidth);
                int byteCounter = 0;
                for(int iYpos = 0; iYpos < m_iImageHeight; iYpos++)
                {
                    for(int iXpos = 0; iXpos < m_iImageWidth; iXpos++)
                    {
                        for(int iChannel = 0; iChannel < 3; iChannel++)
                        {
                            in.get(c);
                            byteCounter++;
                            unsigned char c2 = reinterpret_cast<unsigned char&>(c);
                            m_ImageData->SetPixelValue(m_iImageHeight-iYpos-1, iXpos, iChannel, c2);
                            // Here we use (m_iImageHeight-iYpos-1) since bitmap data is stored "upside down"
                            iLineNumber++;
                        }
                    }
                    while (byteCounter%4 != 0)
                    {
                        in.get(c);
                        byteCounter++;
                    }

                }
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

/***************************************************************************
GetInfoHeaderSize()
***************************************************************************/
unsigned int BitmapData::GetInfoHeaderSize()
{
    return m_iInfoHeaderSize;
}

/***************************************************************************
SetInfoHeaderType()
***************************************************************************/
void BitmapData::SetInfoHeaderType()
{
    //return m_iInfoHeaderSize;
    switch(m_iInfoHeaderSize)
    {
        case 0:
            m_eInfoHeaderType = NOTSPECIFIED;
            break;
        case 12:
            m_eInfoHeaderType = BITMAPCOREHEADER;
            break;
        case 64:
            m_eInfoHeaderType = OS22XBITMAPHEADER64;
            break;
        case 16:
            m_eInfoHeaderType = OS22XBITMAPHEADER16;
            break;
        case 40:
            m_eInfoHeaderType = BITMAPINFOHEADER;
            break;
        case 52:
            m_eInfoHeaderType = BITMAPV2INFOHEADER;
            break;
        case 56:
            m_eInfoHeaderType = BITMAPV3INFOHEADER;
            break;
        case 108:
            m_eInfoHeaderType = BITMAPV4HEADER;
            break;
        case 124:
            m_eInfoHeaderType = BITMAPV5HEADER;
            break;
    }
}

/***************************************************************************
GetInfoHeaderType()
***************************************************************************/
eInfoHeaderType BitmapData::GetInfoHeaderType()
{
    return m_eInfoHeaderType;
}

/***************************************************************************
GetInfoHeaderTypeString()
***************************************************************************/
std::string BitmapData::GetInfoHeaderTypeString(eInfoHeaderType eType)
{
    switch(eType)
    {
        case NOTSPECIFIED:
            return std::string("NOTSPECIFIED");
            break;
        case BITMAPCOREHEADER:
            return std::string("BITMAPCOREHEADER");
            break;
        case OS22XBITMAPHEADER64:
            return std::string("OS22XBITMAPHEADER64");
            break;
        case OS22XBITMAPHEADER16:
            return std::string("OS22XBITMAPHEADER16");
            break;
        case BITMAPINFOHEADER:
            return std::string("BITMAPINFOHEADER");
            break;
        case BITMAPV2INFOHEADER:
            return std::string("BITMAPV2INFOHEADER");
            break;
        case BITMAPV3INFOHEADER:
            return std::string("BITMAPV3INFOHEADER");
            break;
        case BITMAPV4HEADER:
            return std::string("BITMAPV4HEADER");
            break;
        case BITMAPV5HEADER:
            return std::string("BITMAPV5HEADER");
            break;
        default:
            return std::string("NOTSPECIFIED");
            break;
    }
}

/***************************************************************************
GetImageWidthAddress()
***************************************************************************/
int BitmapData::GetImageWidthAddress(eInfoHeaderType eType)
{
    switch(eType)
    {
        case BITMAPINFOHEADER:
            return 18;
            break;
        default:
            return 0;
            break;
    }
}

int BitmapData::GetImageWidthAddress()
{
    return GetImageWidthAddress(m_eInfoHeaderType);
}

int BitmapData::GetImageWidth()
{
    return m_iImageWidth;
}

/***************************************************************************
GetImageHeightAddress()
***************************************************************************/
int BitmapData::GetImageHeightAddress(eInfoHeaderType eType)
{
    switch(eType)
    {
        case BITMAPINFOHEADER:
            return 22;
            break;
        default:
            return 0;
            break;
    }
}

int BitmapData::GetImageHeightAddress()
{
    return GetImageHeightAddress(m_eInfoHeaderType);
}

int BitmapData::GetImageHeight()
{
    return m_iImageHeight;
}

/***************************************************************************
GetImageColorDepthAddress()
***************************************************************************/
int BitmapData::GetImageColorDepthAddress(eInfoHeaderType eType)
{
    switch(eType)
    {
        case BITMAPINFOHEADER:
            return 28;
            break;
        default:
            return 0;
            break;
    }
}

int BitmapData::GetImageColorDepthAddress()
{
    return GetImageColorDepthAddress(m_eInfoHeaderType);
}

int BitmapData::GetImageColorDepth()
{
    return m_iImageColorDepth;
}

/***************************************************************************
PrintBitmapInfo()
***************************************************************************/
void BitmapData::PrintBitmapInfo()
{
    std::cout << "\n";
    std::cout << "======================================================\n";
    std::cout << "Bitmap file information\n";
    std::cout << "======================================================\n";

    std::cout << "File size: " << GetFileSize() << " bytes / " << GetFileSize()/1000 << " kb / " << GetFileSize()/1000000 << " mb\n";
    //std::cout << "File type: " << std::uppercase << std::hex << GetFileType() << std::dec << std::nouppercase << "\n";
    //std::cout << "Image data address: " << std::uppercase << std::hex << GetImageDataAddress() << std::dec << std::nouppercase << "\n";
    //std::cout << "Info header size: " << GetInfoHeaderSize() << "\n";
    //std::cout << "Info header type: " << int(GetInfoHeaderType()) << "\n";
    //std::cout << "Info header type string: " << GetInfoHeaderTypeString(GetInfoHeaderType()) << "\n";
    std::cout << "Image width: " << GetImageWidth() << " pixels\n";
    std::cout << "Image height: " << GetImageHeight() << " pixels\n";
    std::cout << "Image color depth: " << GetImageColorDepth() << " bits\n";

    std::cout << "\n";
}

/***************************************************************************
PrintPixelArray()
***************************************************************************/
void BitmapData::PrintPixelArray(eChannelIndex eChannel)
{
    std::cout << "======================================================\n";
    printf("Bitmap pixel array (channel %d):\n", (int)eChannel);
    std::cout << "======================================================\n";

    //std::cout << std::hex;
    //std::cout << std::setfill('0') << std::setw(2);
    for(int iYpos = 0; iYpos < m_iImageHeight; iYpos++)
    {
        for(int iXpos = 0; iXpos < m_iImageWidth; iXpos++)
        {
            printf("%02x ", m_ImageData->GetPixelValue(iYpos, iXpos, eChannel));
        }
        std::cout << "\n";
    }

    //std::cout << std::dec;

    std::cout << "\n";
}