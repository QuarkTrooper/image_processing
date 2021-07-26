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

    static int GetImageWidthAddress(eInfoHeaderType);
    int GetImageWidthAddress();
    int GetImageWidth();
    static int GetImageHeightAddress(eInfoHeaderType);
    int GetImageHeightAddress();
    int GetImageHeight();
    static int GetImageColorDepthAddress(eInfoHeaderType);
    int GetImageColorDepthAddress();
    int GetImageColorDepth();

    void PrintBitmapInfo();

private:
    uint8_t** m_iImageData;
    int m_iFileSize;
    unsigned int m_iFileType;
    unsigned int m_iImageDataAddress;
    unsigned int m_iInfoHeaderSize;
    unsigned int m_iImageWidth;
    unsigned int m_iImageHeight;
    unsigned int m_iImageColorDepth;
    eInfoHeaderType m_eInfoHeaderType;
};

#endif