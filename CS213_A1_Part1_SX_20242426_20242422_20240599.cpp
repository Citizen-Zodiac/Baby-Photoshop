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
    cout<<"Choose:"<<endl;
    cout<<"1. Simple Frame"<<endl;
    cout<<"2. Fancy Frame"<<endl;
    int c;
    cin>> c;
    switch(c) {
        case 1: {
            int color_index = img.height / 30;

            for (int i = 0; i < img.width; i++)
                for (int j = 0; j < color_index; j++)
                    img(i,j,0) = 255, img(i,j,1) = 255, img(i,j,2) = 255;

            for (int i = 0; i < img.width; i++)
                for (int j = img.height - color_index; j < img.height; j++)
                    img(i,j,0) = 255, img(i,j,1) = 255, img(i,j,2) =255;

            for (int i = 0; i < color_index; i++)
                for (int j = 0; j < img.height; j++)
                    img(i,j,0) = 255, img(i,j,1) = 255, img(i,j,2) = 255;

            for (int i = img.width - color_index; i < img.width; i++)
                for (int j = 0; j < img.height; j++)
                    img(i,j,0) = 255, img(i,j,1) = 255, img(i,j,2) = 255;
            break;
        }
            case 2: {
            //In Fancy Frame I used the same idea before but in for of if conditions.
            //In The Simple Frame it's just for clarifying the mechanism of work by dividing every side alone

            int base = img.height / 100;
            int gap = base / 2;

            int emerald[3] = {0, 64, 60};
            int bronze[3]  = {205, 127, 50};
            int cream[3]   = {250, 240, 210};

            for (int x = 0; x < img.width; x++) {
                for (int y = 0; y < img.height; y++) {
                    if (x < base || x >= img.width - base ||
                        y < base || y >= img.height - base) {
                        img(x, y, 0) = emerald[0];
                        img(x, y, 1) = emerald[1];
                        img(x, y, 2) = emerald[2];
                        }
                }
            }

            int start1 = base + gap;
            int end_width1 = img.width - (base + gap );
            int end_height1 = img.height - (base + gap);

            for (int x = start1; x < end_width1; x++) {
                for (int y = start1 ; y < end_height1; y++) {
                    if (x < start1 + base || x >= end_width1 - base ||
                        y < start1 + base || y >= end_height1 - base) {
                        img(x, y, 0) = bronze[0];
                        img(x, y, 1) = bronze[1];
                        img(x, y, 2) = bronze[2];
                        }
                }
            }

            int start2 = start1 + base + gap;
            int end_width2 = end_width1 - (base + gap);
            int end_height2  = end_height1 - (base + gap);

            for (int x = start2; x < end_width2; x++) {
                for (int y = start2; y < end_height2; y++) {
                    if (x < start2 + base || x >= end_width2 - base ||
                        y < start2 + base || y >= end_height2 - base) {
                        img(x, y, 0) = cream[0];
                        img(x, y, 1) = cream[1];
                        img(x, y, 2) = cream[2];
                        }
                }
            }

             break;

        }
            default: {
            cout<<"Invalid Option"<<endl;
            break;
        }

     }




}
void purple(Image &img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {

            int r = min(255,int(1.3*img(i, j, 0)));
            int g = min(255,int(0.7*img(i, j, 1)));
            int b = min(255,int(1.3*img(i, j, 2)));
            img(i, j, 0) = r;
            img(i, j, 1) = g;
            img(i, j, 2) = b;

        }
    }
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