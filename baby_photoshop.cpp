#include <bits/stdc++.h>
using namespace std;
#include "Image_Class.h"



void BlackAndWhite(Image& image, int compar_point = 128)
{
    for(int i = 0; i < image.width; ++i)
    {
        for(int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0;
            for(int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k);
            }
            avg /= 3;
            unsigned int new_pix = (avg >= compar_point) ? 255 : 0;
            for (int k = 0; k < 3; ++k)
            {
                image.setPixel(i, j, k, new_pix);
            }
            
        }
    }
}

int main()
{
    string fileName;
    cout << "Please enter image filename to open: ";
    cin >> fileName;
    
    Image image(fileName);
    
    cout << "Enter output filename (with extension .jpg, .bmp, .png, .tga): ";
    cin >> fileName;
    image.saveImage(fileName);
}