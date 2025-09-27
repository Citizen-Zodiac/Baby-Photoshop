#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

void invert(Image& img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                img(i, j, k) = 255 - img(i, j, k);
            }
        }
    }
}
void blur(Image& img) {
    Image temp=img;
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {

            //Kernel Loops
            int sum[3]={0,0,0},pixel_cnt=0;

            for (int x = i-2; x <= i+2; x++) {
                for (int y = j-2; y <= j+2; y++) {
                    if (x>=0 && x<img.width && y>=0 && y<img.height) {
                        for (int k = 0; k < 3; k++) {
                             sum[k]+= temp(x, y, k);
                        }
                        pixel_cnt++;
                    }
                }

            }
            // OverWriting The Pixel With Kernel Values
            for (int k = 0; k < 3; k++) {
                img(i, j, k) = sum[k]/pixel_cnt;
            }
        }
    }
}


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

void Flip(Image& image) 
{
    Image temp = image; 

    int choice;     
    cout << "Choose flip type:\n";
    cout << "1 - Horizontal Flip (Left-Right)\n";
    cout << "2 - Vertical Flip (Top-Bottom)\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1)
    {
        for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                image(i, j, k) = temp(image.width - 1 - i, j, k);
            }
        }
    }
    }
        
    else if (choice == 2)
    {
        for (int i = 0; i < image.width; ++i) 
        {
           for (int j = 0; j < image.height; ++j) 
           {
            for (int k = 0; k < image.channels; ++k) 
            {
                image(i, j, k) = temp(i, image.height - 1 - j, k);
            }
           }
       }
    }
    else
        cout << "Invalid choice.\n";

}


int main() {
    string filename;
    cout << "Enter Image Name With Extension: "<<endl;
    cin >> filename;

    Image image(filename);

    blur(image);
    cout<<"Please Enter The Name To Export The Photo W/ Extension: "<<endl;
    cin >> filename;

    image.saveImage(filename);

    return 0;
}
