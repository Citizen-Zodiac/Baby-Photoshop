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
    cout<<"Please Enter Blur Intensity Index From 1 : 7"<<endl;
    int index;
    cin >> index; if(index>7)index=7;
    index++;
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {

            //Kernel Loops
            int sum[3]={0,0,0},pixel_cnt=0;

            for (int x = i-index; x <= i+index; x++) {
                for (int y = j-index; y <= j+index; y++) {
                    if (x>=0 && x<img.width && y>=0 && y<img.height) {
                        sum[0] += temp(x,y,0);
                        sum[1] += temp(x,y,1);
                        sum[2] += temp(x,y,2);

                        pixel_cnt++;
                    }
                }

            }
            // OverWriting The Pixel With Kernel Values

                img(i, j, 0) = sum[0]/pixel_cnt;
                img(i, j, 1) = sum[1]/pixel_cnt;
                img(i, j, 2) = sum[2]/pixel_cnt;

        }
    }
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
