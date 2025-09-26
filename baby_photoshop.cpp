#include<bits/stdc++.h>
#include "Image_class.h"
using namespace std;

Image grayScale(Image& image)
{
    for(int i=0;i<image.width;i++)
    {
        for(int j=0;j<image.height; j++)
        {
            unsigned int avg=0;
            for(int k=0;k<3; k++){
                avg += image(i,j,k); 
            }
            avg =avg/3;
            for(int k=0;k<3;k++)
            {
                image(i,j,k) =avg;
            }
        }
    }
    return image;
}

Image merge(Image&image1, Image&image2)
{
    int w=min(image1.width,image2.width);
    int h=min(image1.height,image2.height);
    

    Image temp(w,h);
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++)
        {
            for(int k=0;k<2;k++){
                temp(i,j,k)=(image1(i,j,k) + image2(i,j,k)) / 2;
            }
        }
        
    }   


    return temp;

    
}



int main(){
    // enter image;
    string filename;
    cout << "Pls enter colored image name to turn to gray scale: ";
    cin >> filename;

    Image image(filename);

    // save image;
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;

    image.saveImage(filename);


}