#include "hexTexture.hpp"

HexTexture::HexTexture(std::string path, int hexWidth, int hexHeight, int peakHeight) : Texture(path)
{
    this->hexWidth = hexWidth;
    this->hexHeight = hexHeight;
    this->peakHeight = peakHeight;
}

HexTexture::~HexTexture()
{

}
/* 
void HexTexture::render(double centerX, double centerY, double customWidth)
{
    double ratioHW = (double)height / (double)width;
    double ratioWH = (double)width / (double)height;
    double customHeight = ratioHW * customWidth;
    std::cout << "customHeight: " << customHeight << " customWidth: " << customWidth <<  " ratioHW: " << ratioHW << std::endl;
    std::cout << "centerX :" << this->centerX << " width: " << width << std::endl;
    Texture::render(centerX - customWidth / 2 - 1, centerY - this->centerY * ratioHW, customWidth, customHeight);
//    Texture::render(centerX - this->centerX, centerY - this->centerY, width, height);
    Graphics::instance()->drawPoint(centerX - this->centerX, centerY - this->centerY);
}
*/