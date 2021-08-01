#include"PixelArray.h"

/***************************************************************************
Constructor
***************************************************************************/
PixelArray::PixelArray()
{
    m_piImageData = nullptr;
}
PixelArray::PixelArray(int imageHeight, int imageWidth)
{
    m_iImageHeight = imageHeight;
    m_iImageWidth = imageWidth;
    m_piImageData = new unsigned char[3*imageWidth*imageHeight];
}

/***************************************************************************
Destructor
***************************************************************************/
PixelArray::~PixelArray()
{
    delete m_piImageData;
}

/***************************************************************************
Init()
***************************************************************************/
void PixelArray::Init(int imageHeight, int imageWidth)
{
    if(m_piImageData != nullptr)
    {
        delete m_piImageData;
    }
    m_piImageData = new unsigned char[3*imageWidth*imageHeight];
}

/***************************************************************************
SetPixelValue()
***************************************************************************/
void PixelArray::SetPixelValue(int yPos, int xPos, int channel, int value)
{
    if(m_piImageData != nullptr)
    {
        m_piImageData[3*yPos*m_iImageWidth + 3*xPos + channel] = (unsigned char)value;
    }
}

/***************************************************************************
GetPixelValue()
***************************************************************************/
unsigned char PixelArray::GetPixelValue(int yPos, int xPos, eChannelIndex channel)
{
    if(m_piImageData != nullptr)
    {
        return m_piImageData[3*yPos*m_iImageWidth + 3*xPos + (int)channel];
    }
    else
    {
        return 0;
    }
}