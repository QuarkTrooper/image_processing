#ifndef _BITMAPFILEENUMS_
#define _BITMAPFILEENUMS_

#define ADDR_FILE_TYPE 0
#define ADDR_FILE_TYPE_BYTES 2

#define ADDR_FILE_BYTESIZE 2
#define ADDR_FILE_BYTESIZE_BYTES 4

#define ADDR_DATA_OFFSET 10
#define ADDR_DATA_OFFSET_BYTES 4

#define ADDR_HEADER_TYPE 14
#define ADDR_HEADER_TYPE_BYTES 4

enum eInfoHeaderType
{
    NOTSPECIFIED = -1,
    BITMAPCOREHEADER = 0,
    OS22XBITMAPHEADER64,
    OS22XBITMAPHEADER16,
    BITMAPINFOHEADER,
    BITMAPV2INFOHEADER,
    BITMAPV3INFOHEADER,
    BITMAPV4HEADER,
    BITMAPV5HEADER
};

enum eChannelIndex
{
    eBLUE = 0,
    eGREEN = 1,
    eRED = 2
};

#endif