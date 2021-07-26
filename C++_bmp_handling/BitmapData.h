#ifndef _BITMAPDATA_
#define _BITMAPDATA_

class BitmapData
{
public:
    BitmapData();
    ~BitmapData();

    void LoadImage(const char*);
    int GetFileSize();
    unsigned int GetFileType();
    unsigned int GetImageDataAddress();
private:
    uint8_t** m_iImageData;
    int m_iFileSize;
    unsigned int m_iFileType;
    unsigned int m_iImageDataAddress;
};

#endif