#ifndef _BITMAPDATA_
#define _BITMAPDATA_

class BitmapData
{
public:
    BitmapData(){};
    ~BitmapData(){};

    LoadImage(const char*);
private:
    uint8_t** iImageData;
};

#endif