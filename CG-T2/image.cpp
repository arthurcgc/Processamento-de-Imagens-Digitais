#include "image.h"

#include <QtMath>
#include <math.h>

Image::Image()
    : _width(0), _height(0), _depth(0)
{
}


Image::Image(const Image& orig)
    : _width(orig._width)
    , _height(orig._height)
    , _depth(orig._depth)
    , _buffer(orig._buffer)
{
}


Image::Image(int width, int height, int depth)
    : _width(width)
    , _height(height)
    , _depth(depth)
    , _buffer(_width * _height * _depth, 0.0f) //Inicializa o buffer com 0's
{
}


Image::Image(int width, int height, int depth, float* buffer)
    : _width(width)
    , _height(height)
    , _depth(depth)
    , _buffer(buffer, buffer + _width * _height * _depth)
{
}


Image::~Image()
{
}


void Image::getDimensions(int& width, int& height, int& depth)
{
    width = _width;
    height = _height;
    depth = _depth;
}


std::vector<float>& Image::getColorBuffer()
{
    return _buffer;
}


Image Image::toGrayscale()
{
    if (_depth==1) return *this;

    Image outImage(_width,_height, 1);

    std::vector<float>& dst = outImage.getColorBuffer();

    for( int y = 0; y < _height; y++ )
    {
        for( int x = 0; x < _width; x++ )
        {
            int k = y*_width*_depth+x*_depth;
            dst[y*_width+x]=0.2126f*_buffer[k] +0.7152f*_buffer[k+1]+0.0722f*_buffer[k+2];
        }
    }
   return outImage;
}


void Image::fromQImage(const QImage &qImage)
{
    if( !qImage.isNull() )
    {
        _buffer.clear();

        _width = qImage.width();
        _height = qImage.height();
        _depth = qImage.isGrayscale() ? 1 : 3;

        _buffer.resize(_width*_height*_depth, 0.0f);

        int pos = 0;
        for( int y = 0; y < _height; y++ )
        {
            for( int x = 0; x < _width; x++ )
            {
                QColor color = qImage.pixel(x,y);

                _buffer[pos++] = color.red()/255.f;

                if( _depth == 3 )
                {
                    _buffer[pos++] = color.green()/255.f;
                    _buffer[pos++] = color.blue()/255.f;
                }
            }
        }
    }
}


unsigned char fix(float value){
    value=(value<0)?-value:value;
    value=(value>1)?1:value;
    return (unsigned char) (255*value);
}


QImage Image::toQImage()
{
    QImage qImage( _width, _height, QImage::Format_RGB32 );

    if( !_buffer.empty() )
    {
        int pos = 0;
        for( int y = 0; y < _height; y++ )
        {
            for( int x = 0; x < _width; x++ )
            {
                float value = fix(_buffer[pos++]);
                QColor color(value, value, value);

                if( _depth == 3 )
                {
                    color.setGreen(fix(_buffer[pos++]));
                    color.setBlue(fix(_buffer[pos++]));
                }

                qImage.setPixelColor(x,y,color);
            }
        }
    }
    return qImage;
}


/** Algoritmos a serem implementados **/



int Image::GetIndex(int x,int y)
{
    return y * _width * _depth + x * _depth;
}

void Image::Multiply(int i, int j,float kernel[3][3],float rgb[3])
{
    rgb[0]=rgb[1]=rgb[2]=0;
    int maxpos=_width*_height*_depth;

    for (int x=0;x<3;++x)
    {
        for (int y=0;y<3;++y)
        {
            int index=GetIndex(i+x-1,j+y-1);
            if (index<0||index>=maxpos) continue;
            rgb[0]+=kernel[x][y]*_buffer[index];
            if(_depth==3) {
            rgb[1]+=kernel[x][y]*_buffer[index+1];
            rgb[2]+=kernel[x][y]*_buffer[index+2];
            }
        }
    }
if(kernel[1][1]==0){
        rgb[0]/=4.0;
    }


else if(kernel[1][1]==4){
    rgb[0]/=16.0;
    rgb[1]/=16.0;
    rgb[2]/=16.0;
}
}

void Image::SetBuffer(int pos,float rgb[3]){
    _buffer[pos]=rgb[0];
    if(_depth==1) return;
    _buffer[pos+1]=rgb[1];
    _buffer[pos+2]=rgb[2];
}



void smoothing(Image& input, Image& output)
{
    output = Image(input);
    int w,h,d;
    input.getDimensions(w,h,d);
    for( int y = 1; y <h-1; y++ )
    {
        for( int x = 1; x < w-1; x++ )
        {
            float kernel[3][3];
            kernel[0][0]=1;kernel[0][1]=2;kernel[0][2]=1;
            kernel[1][0]=2;kernel[1][1]=4;kernel[1][2]=2;
            kernel[2][0]=1;kernel[2][1]=2;kernel[2][2]=1;
            int pos=output.GetIndex(x,y);
            float rgb[3];
            input.Multiply(x,y,kernel,rgb);
            output.SetBuffer(pos,rgb);
        }
    }
    }

void sobel(Image& input, Image& output)
{
    output=Image(input);
    output=output.toGrayscale();
    int w,h,d;
    input.getDimensions(w,h,d);
    for( int y = 1; y <h-1; y++ )
    {
        for( int x = 1; x < w-1; x++ )
        {
            float kernelx[3][3];
            kernelx[0][0]=-1;kernelx[0][1]=0;kernelx[0][2]=1;
            kernelx[1][0]=-2;kernelx[1][1]=0;kernelx[1][2]=2;
            kernelx[2][0]=-1;kernelx[2][1]=0;kernelx[2][2]=1;
            int pos=output.GetIndex(x,y);
            float rgbx[3];
            input.Multiply(x,y,kernelx,rgbx);
            float kernely[3][3];
            kernely[0][0]=-1;kernely[0][1]=-2;kernely[0][2]=-1;
            kernely[1][0]=0;kernely[1][1]=0;kernely[1][2]=0;
            kernely[2][0]=1;kernely[2][1]=2;kernely[2][2]=1;
            float rgby[3];
            input.Multiply(x,y,kernely,rgby);
            float rgb[3];
            rgb[0]=sqrt(pow(rgbx[0],2)+pow(rgby[0],2));
            rgb[1]=sqrt(pow(rgbx[1],2)+pow(rgby[1],2));
            rgb[2]=sqrt(pow(rgbx[2],2)+pow(rgby[2],2));
            output.SetBuffer(pos,rgb);
        }
}
}






void haar(Image& input, Image& output)
{
    output = Image(input);
    int w,h,d;
    input.getDimensions(w,h,d);
    int hh=0.5*h;
    int hw=0.5*w;
    std::vector<float>& bf = input.getColorBuffer();

    // Agora o algoritmo na vertical
for(int x = 0; x <w; x++)
{
    for(int y = 0; y <hh; y++)
    {
        int posl=output.GetIndex(x,y);
        int pospares=output.GetIndex(x,2*y);
        int posr=output.GetIndex(x,y+hh);
        float rgbl[3];
        float rgbr[3];

        if (d==1){
            rgbl[0]=0.5*(bf[pospares]+bf[pospares+d]);
            rgbr[0]=0.5*(bf[pospares]-bf[pospares+d]);
        }
        else{
            rgbl[0]=0.5*(bf[pospares]+bf[pospares+d]);
            rgbl[1]=0.5*(bf[pospares+1]+bf[pospares+d+1]);
            rgbl[2]=0.5*(bf[pospares+2]+bf[pospares+d+2]);
            rgbr[0]=0.5*(bf[pospares]-bf[pospares+d]);
            rgbr[1]=0.5*(bf[pospares+1]-bf[pospares+d+1]);
            rgbr[2]=0.5*(bf[pospares+2]-bf[pospares+d+2]);
        }

        output.SetBuffer(posl,rgbl);
        output.SetBuffer(posr,rgbr);
    }
}
    bf=output.getColorBuffer();

    for(int y = 0; y <h; y++)
    {
        for( int x = 0; x <hw; x++)
        {
            int posl=output.GetIndex(x,y);
            int pospares=output.GetIndex(2*x,y);
            int posr=output.GetIndex(x+hw,y);
            float rgbl[3];
            float rgbr[3];
            if (d==1){
                rgbl[0]=0.5*(bf[pospares]+bf[pospares+d]);
                rgbr[0]=0.5*(bf[pospares]-bf[pospares+d]);
            }
            else{
                rgbl[0]=0.5*(bf[pospares]+bf[pospares+d]);
                rgbl[1]=0.5*(bf[pospares+1]+bf[pospares+d+1]);
                rgbl[2]=0.5*(bf[pospares+2]+bf[pospares+d+2]);
                rgbr[0]=0.5*(bf[pospares]-bf[pospares+d]);
                rgbr[1]=0.5*(bf[pospares+1]-bf[pospares+d+1]);
                rgbr[2]=0.5*(bf[pospares+2]-bf[pospares+d+2]);
            }
            output.SetBuffer(posl,rgbl);
            output.SetBuffer(posr,rgbr);
        }
     }

}


void haarInv(Image& input, Image& output)
{
    output = Image(input);
    int w,h,d;
    input.getDimensions(w,h,d);
    int hh=0.5*h;
    int hw=0.5*w;
    std::vector<float>& bf = input.getColorBuffer();
    for( int y = 0; y <h; y++ )
    {
        for( int x = 0; x < hw; x++ )
        {
            int ai=output.GetIndex(x,   y);
            int di=output.GetIndex(x+hw,y);
            int ii=output.GetIndex(2*x, y);
            int ij=output.GetIndex(2*x+1,y);
            float rgbl[3];
            float rgbr[3];
            if (d==1){
                rgbl[0]=bf[ai]+bf[di];
                rgbr[0]=bf[ai]-bf[di];
            }
            else{
                rgbl[0]=bf[ai]  +bf[di];
                rgbl[1]=bf[ai+1]+bf[di+1];
                rgbl[2]=bf[ai+2]+bf[di+2];
                rgbr[0]=bf[ai]  -bf[di];
                rgbr[1]=bf[ai+1]-bf[di+1];
                rgbr[2]=bf[ai+2]-bf[di+2];
            }
            output.SetBuffer(ii,rgbl);
            output.SetBuffer(ij,rgbr);
        }
    }
    bf=output.getColorBuffer();
    for( int x = 0; x <w; x++ )
    {
        for( int y = 0; y < hh; y++ )
        {
            int ai=output.GetIndex(x,   y);
            int di=output.GetIndex(x,y+hh);
            int ii=output.GetIndex(x,2*y);
            int ij=output.GetIndex(x,2*y+1);
            float rgbl[3];
            float rgbr[3];
            if (d==1){
                rgbl[0]=bf[ai]+bf[di];
                rgbr[0]=bf[ai]-bf[di];
            }
            else{
                rgbl[0]=bf[ai]  +bf[di];
                rgbl[1]=bf[ai+1]+bf[di+1];
                rgbl[2]=bf[ai+2]+bf[di+2];
                rgbr[0]=bf[ai]  -bf[di];
                rgbr[1]=bf[ai+1]-bf[di+1];
                rgbr[2]=bf[ai+2]-bf[di+2];
            }
            output.SetBuffer(ii,rgbl);
            output.SetBuffer(ij,rgbr);
        }
    }
}

void enhanceHaar(Image& input, Image& output)
{
    output = Image(input);
    int w,h,d;
    input.getDimensions(w,h,d);
    std::vector<float>& bf = input.getColorBuffer();

    for( int y = 0.5*h; y <h; y++ )
    {
        for( int x = 0; x < w; x++ )
        {
            int pos=output.GetIndex(x,y);
            float rgb[3];
            rgb[0]=10*bf[pos];
            rgb[1]=10*bf[pos+1];
            rgb[2]=10*bf[pos+2];
            output.SetBuffer(pos,rgb);
        }
    }
        for( int y = 0; y <h*0.5; y++ )
        {
            for( int x = 0.5*w; x < w; x++ )
            {
                int pos=output.GetIndex(x,y);
                float rgb[3];
                rgb[0]=10*bf[pos];
                rgb[1]=10*bf[pos+1];
                rgb[2]=10*bf[pos+2];
                output.SetBuffer(pos,rgb);
            }
        }

}
