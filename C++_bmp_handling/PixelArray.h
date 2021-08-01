#ifndef _PIXELARRAY_
#define _PIXELARRAY_

#include "BitmapFileAddresses.h"

class PixelArray
{
public:
    PixelArray();
    PixelArray(int, int);
    ~PixelArray();

    void Init(int, int);
    void SetPixelValue(int, int, int, int);
    unsigned char GetPixelValue(int, int, eChannelIndex);
private:
    unsigned char* m_piImageData;
    int m_iImageHeight;
    int m_iImageWidth;
};


#endif