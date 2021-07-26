#ifndef _BITMAPDATA_
#define _BITMAPDATA_

#include "BitmapFileAddresses.h"
#include <string>

class BitmapData
{
public:
    BitmapData();
    ~BitmapData();

    void LoadImage(const char*);
    int GetFileSize();
    unsigned int GetFileType();
    unsigned int GetImageDataAddress();
    unsigned int GetInfoHeaderSize();
    void SetInfoHeaderType();
    eInfoHeaderType GetInfoHeaderType();
    std::string GetInfoHeaderTypeString(eInfoHeaderType);

    void PrintBitmapData();

private:
    uint8_t** m_iImageData;
    int m_iFileSize;
    unsigned int m_iFileType;
    unsigned int m_iImageDataAddress;
    unsigned int m_iInfoHeaderSize;
    eInfoHeaderType m_eInfoHeaderType;
};

#endif