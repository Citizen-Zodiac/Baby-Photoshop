/*
    Course: CS213 "OOP" - Assignment 1 - Part 1
    Section: 23/24

    File description:
                This program works with images by applying different filters 
                such as (GrayScale, Merge, Invert, Blur, Black & White, and Flip). 
                The program provides a menu that allows the user to load a new image, 
                apply any filter, and save the image after changes.

    Team members:   
            Id                Name                    Filters
        - 20240599      Mustafa Mahmoud     -> Implemented GrayScale, Merge
        - 20242426      Mohamed Ibrahim    -> Implemented Invert, Blur
        - 20242422      Hamza Mohamed     -> Implemented Black & White, Flip


*/

#include<bits/stdc++.h>
#include "Image_class.h"
using namespace std;

void grayScale(Image& image) {
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
            for(int k=0;k<3;k++){
                temp(i,j,k)=(image1(i,j,k) + image2(i,j,k)) / 2;
            }
        }
        
    }   
    return temp;
}

void invert(Image& img) 
{
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                img(i, j, k) = 255 - img(i, j, k);
            }
        }
    }
}


void blur(Image& img) 
{
    cout<<"Please Enter Blur Intensity Index From 1 : 5"<<endl;
    int index;
    cin >> index; if(index>5)index=5;else if(index<=0)index=1;
    index=index+3;
    Image temp=img;
    while (index--) {
        for (int i = 0; i < img.width; i++) {
            for (int j = 0; j < img.height; j++) {

                //Kernel Loops
                int sum[3]={0,0,0},pixel_cnt=0;

                for (int x = i-3; x <= i+3; x++) {
                    for (int y = j-3; y <= j+3; y++) {
                        if (x>=0 && x<img.width && y>=0 && y<img.height) {
                            sum[0] += temp(x,y,0);
                            sum[1] += temp(x,y,1);
                            sum[2] += temp(x,y,2);

                            pixel_cnt++;
                        }
                    }

                }
                // OverWriting The Pixel With Kernel Values

                    temp(i, j, 0) = sum[0]/pixel_cnt;
                    temp(i, j, 1) = sum[1]/pixel_cnt;
                    temp(i, j, 2) = sum[2]/pixel_cnt;

            }
        }
    swap(img,temp);
    }
}

void rotate(Image &img) {
    cout<<"1=> "<<"90 Degree Clockwise\n";
    cout<<"2=> "<<"180 Degree Clockwise\n";
    cout<<"3=> "<<"270 Degree Clockwise\n";
    int no;
    cin>>no;


    switch(no) {

            case 1: {
                // New Dimensions
                int new_width  = img.height;
                int new_height = img.width;
                Image temp(new_width, new_height);

                for (int x = 0; x < img.width; x++) {
                    for (int y = 0; y < img.height; y++) {
                        for (int k = 0; k < img.channels; k++) {
                            int new_x = img.height - 1 - y;
                            int new_y = x;
                            temp(new_x, new_y, k) = img(x, y, k);
                        }
                    }
                }
                swap(img, temp);
                break;
            }
            case 2: {
        Image temp(img.width, img.height);

        for (int x = 0; x < img.width; x++) {
            for (int y = 0; y < img.height; y++) {
                for (int k = 0; k < img.channels; k++) {
                    int new_x = img.width - 1 - x;
                    int new_y = img.height - 1 - y;
                    temp(new_x, new_y, k) = img(x, y, k);
                }
            }
        }
                swap(img, temp);
                break;
    }
        case 3: {
                int new_width  = img.height;
                int new_height = img.width;
                Image temp(new_width, new_height);

                for (int x = 0; x < img.width; x++) {
                    for (int y = 0; y < img.height; y++) {
                        for (int k = 0; k < img.channels; k++) {
                            int new_x = y;
                            int new_y = img.width - 1 - x;
                            temp(new_x, new_y, k) = img(x, y, k);
                        }
                    }
                }
                swap(img, temp);
                break;
        }
            default: {
                cout<<"Invalid Option";
            }

    }
}
void frame(Image &img) {
    int thickness = img.height / 30;

    // top
    for (int i = 0; i < img.width; i++)
        for (int j = 0; j < thickness; j++)
            img(i,j,0) = 255, img(i,j,1) = 0, img(i,j,2) = 0;

    // bottom
    for (int i = 0; i < img.width; i++)
        for (int j = img.height - thickness; j < img.height; j++)
            img(i,j,0) = 255, img(i,j,1) = 0, img(i,j,2) = 0;

    // left
    for (int i = 0; i < thickness; i++)
        for (int j = 0; j < img.height; j++)
            img(i,j,0) = 255, img(i,j,1) = 0, img(i,j,2) = 0;

    // right
    for (int i = img.width - thickness; i < img.width; i++)
        for (int j = 0; j < img.height; j++)
            img(i,j,0) = 255, img(i,j,1) = 0, img(i,j,2) = 0;
}

void blackAndWhite(Image& image)
{
    const int compar_point = 128;
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

void flip(Image& image) 
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

void crop_image(Image& image)
{       
    int x, y, cropWidth, cropHeight;

    cout << "Enter top-left corner (x , y): ";
    cin >> x >> y;
    cout << "Enter crop width and height: ";
    cin >> cropWidth >> cropHeight;

    if (x < 0 || y < 0 || x + cropWidth > image.width || y + cropHeight > image.height) {
        throw invalid_argument("Crop dimensions are out of image bounds.");
    }

    Image croppedImage(cropWidth, cropHeight);

    for(int i = 0; i < cropWidth; ++i)
    {
        for(int j = 0; j < cropHeight; ++j)
        {
            for(int k = 0; k < 3; ++k)
            {
                croppedImage(i, j, k) = image(i + x, j + y, k);
            }
        }
    }
    image = croppedImage;
} 

void resize(Image& image)
{
    int choice;
    cout << "Do You Prefer Entering: [1] New Dimensions [2] ratio ?" <<  endl;
    cin >> choice;
    
    int newWidth, newHeight;
    float ratio;

    if(choice == 1)
    {
        cout << "Enter the Resize dimensions: " << endl;
        cin >> newWidth >> newHeight;
    }
    else if(choice == 2)
    {
        cout << "Enter Scaling Ratio (Ex: 0.5 for half size): ";
        cin >> ratio;
        newWidth = image.width * ratio;
        newHeight = image.height * ratio;
    }
    else
    {
        throw invalid_argument("Sorry, not an option");
    }
    if (newWidth <= 0 || newHeight <= 0) 
    {
    throw invalid_argument("Resize dimensions are invalid.");
    }

    Image resizedImage(newWidth,newHeight);

    float scaleX = (float)image.width / resizedImage.width;
    float scaleY = (float)image.height / resizedImage.height;

    for (int i = 0; i < resizedImage.width; ++i)
    {
        for (int j = 0; j < resizedImage.height; ++j)
        {
            int X = min((int)(i * scaleX), image.width - 1);
            int Y = min((int)(j * scaleY), image.height - 1);
            for(int k = 0; k < 3; ++k)
            {
                resizedImage(i, j, k) = image(X, Y, k);
            }
        }
        
    }
    image = resizedImage;
}

void display()
{
    cout<<"1 -> Load a new image\n";
    cout<<"2 -> Gray Scale\n";
    cout<<"3 -> Merge\n";
    cout<<"4 -> Invert\n";
    cout<<"5 -> Blur\n";
    cout<<"6 -> Black & White\n";
    cout<<"7 -> Flip\n";
    cout<<"8 -> Save the image\n";
    cout<<"0 -> Exit\n";
}

int fnum; // to check if apply any filters or no And global to save func see it to rest it after save
string filename; // global to save func see it;
void save(Image&image)
{
        cout<<"Save with the same name? Yes or No : ";
        string chose;
        getline(cin, chose);

        if(chose=="yes"||chose=="Yes")
        {
            image.saveImage(filename);
        }
        else
        {
            bool loaded = false;
            cout << "Pls enter The Image Name with Extension: ";
            getline(cin,filename);
            while (!loaded)
            {

                try
                {
                    if (filename.size() < 4)
                        throw invalid_argument("Filename it's short for valid extension.");

                    string ex = filename.substr(filename.size()-4);

                    if (ex == ".png" || ex == ".jpg" || ex == ".bmp" || ex == ".tga") {
                        image.saveImage(filename);
                        loaded = true;
                    }
                    else {
                        throw invalid_argument("Invalid extension! pls only (.png, .jpg, .bmp, .tga).");
                    }
                }
                catch (const invalid_argument& e)
                {
                    cout <<"$ "<< e.what() <<" $"<< endl;
                    cout << "Pls enter another filename: ";
                    getline(cin, filename);
                }
            }

        }
        cout<<"Image Saved: "<<filename<<endl;
        fnum=0;
}

Image image;  // to see it every funcs;
void check_filter_apply(int fn)
{
    string ch;
    if(fn>0)
    {
        cout<<"Save current file? Yes or No: ";
        cin>>ch;
        cin.ignore();

        if(ch=="Yes"||ch=="yes"){
            save(image);
        }
        else if(ch=="No" || ch=="no"){
            return;
        }
        else{
            check_filter_apply(fn);
        }
    }
}


int main()
{
    cout << "Pls enter The Image Name with Extension: ";
    getline(cin,filename);

    bool loaded = false;

    while (!loaded)
    {
        try{
            image=Image(filename);
            loaded=true;
        }

        catch(const invalid_argument&e)
        {
            cout << "Invalid file! Pls enter a valid image with extension: ";
            getline(cin,filename);
        }
    }

    fnum=0;
    int c=-1; // number of choice
    while(c!=0)
    {
        display();
        cin>>c;
        cin.ignore();

        switch(c)
        {
            case 1:
            {
                check_filter_apply(fnum);
                cout << "Pls enter The Image Name with Extension: ";
                getline(cin,filename);

                bool loaded_n = false;

                while (!loaded_n)
                {
                    try{
                        image=Image(filename);
                        loaded_n=true;
                    }

                    catch(const invalid_argument&e)
                    {
                        cout << "Invalid file! Pls enter a valid image with extension: ";
                        getline(cin,filename);
                    }
                }
                break;
            }

            case 2:
            {
                grayScale(image);
                fnum++;
                break;
            }

            case 3:
            {
                Image temp=image;
                Image image2;
                cout<<"Pls enter another image to merge with the first: ";
                string filename2;
                getline(cin,filename2);

                bool loaded2=false;
                while(!loaded2)
                {
                    try{
                        image2=Image(filename2);
                        loaded2=true;
                    }

                    catch(const invalid_argument&e)
                    {
                        cout << "Invalid file! Pls enter a valid image with extension: ";
                        getline(cin,filename2);
                    }
                }
                image=merge(temp,image2);
                fnum++;
                break;
            }
            case 4:
            {
                invert(image);
                fnum++;
                break;
            }

            case 5:
            {
                blur(image);
                fnum++;
                break;
            }


            case 6:
            {
                blackAndWhite(image);
                fnum++;
                break;
            }

            case 7:
            {
                flip(image);
                fnum++;
                break;
            }
            case 8:
            {
                save(image);

                break;
            }
            case 0:
            {
                check_filter_apply(fnum);
                c=0;
                break;
            }
            default :
            {
                display();
                break;
            }
        }
    }

}