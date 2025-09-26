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