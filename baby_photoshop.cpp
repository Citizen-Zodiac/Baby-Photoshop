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

int main() {
    string filename;
    cout << "Enter Image Name With Extension: "<<endl;
    cin >> filename;

    Image image(filename);

    invert(image);
    cout<<"Please Enter The Name To Export The Photo W/ Extension: "<<endl;
    cin >> filename;

    image.saveImage(filename);

    return 0;
}
