/*
Faculty of Computers and Artificial Intelligence (FCAI) - Cairo University
Course: CS213 - Object-Oriented Programming
Assignment 1 - Part 2
Professor: Dr. Mohammed El-Ramly
Academic Year: Semester 1 || 2025
Section: 32

Video Link:
@Author: Hamza Mohamed
https://drive.google.com/file/d/1ijgfcgeZLgXt6LOyN007oiWd4AZlsT9D/view?usp=drive_link

Diagram System Link:
@Author: Mustafa Mahmoud
https://viewer.diagrams.net/?tags=%7B%7D&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=A1.drawio&dark=auto#Uhttps%3A%2F%2Fdrive.google.com%2Fuc%3Fid%3D1y4ZKj-HrFCZIQBt15y9W0xnAFGSWBACI%26export%3Ddownload

Document Link:
@Author: Mohamed Ibrahim
https://docs.google.com/document/d/12wd-_WUsd63VfDKV-3N_4SkHwdYngIee/edit?usp=sharing&ouid=109479120355123432301&rtpof=true&sd=true


Repo Link:
@Author : Mohamed Ibrahim
https://github.com/Citizen-Zodiac/Baby-Photoshop.git


Team Members:
    ID           | Name              | Implemented Filters
    -----------------------------------------------------
    20240599     | Mustafa Mahmoud   | GrayScale, Merge, Darken & Lighten, Edge Detection,Sunlight ,Menu
    20242426     | Mohamed Ibrahim   | Invert, Blur, Rotate, Frame, Purple
    20242422     | Hamza Mohamed     | Black & White, Flip, Resize, Crop, Infrared

Program Description:
This program works with images by applying different filters such as
""GrayScale, Merge, Invert, Blur, Black & White,Flip, Darken & Lighten, Edge detection,
Rotate, Add frame, Purple, Resize, Crop, Infrared,Sunlight.

It also provides a menu that allows the user to load a new image,
apply any filter, and save the image after modifications.

*/

#include<bits/stdc++.h>
#include "Image_class.h"
using namespace std;

void grayScale(Image& image)
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

void invert(Image& image)
{
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
}


void blur(Image& image)
{
    cout<<"Please Enter Blur Intensity Index From 1 : 5"<<endl;
    int index;
    cin >> index; if(index>5)index=5;else if(index<=0)index=1;
    index=index+3;
    Image temp=image;
    while (index--) {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {

                //Kernel Loops
                int sum[3]={0,0,0},pixel_cnt=0;

                for (int x = i-3; x <= i+3; x++) {
                    for (int y = j-3; y <= j+3; y++) {
                        if (x>=0 && x<image.width && y>=0 && y<image.height) {
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
    swap(image,temp);
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


void darken_lighten(Image& image)
{
    int choose;
    cout << "Enter 1 for Darken Or 2 for Lighten: ";
    cin >> choose;

    if(choose == 2)
    {
        for(int i=0;i<image.width;i++){
            for(int j=0;j<image.height;j++){
                for(int k=0;k<3;k++){
                    image(i,j,k) = min(255, image(i,j,k) +255/2);
                }
            }
        }
    }
    else if(choose==1)
    {
        for(int i=0;i<image.width;i++){
            for(int j=0;j<image.height;j++){
                for(int k=0;k<3;k++){
                    image(i,j,k) = image(i,j,k) / 2;
                }
            }
        }
    }
    else{
        cout << "Invalid choice! Please enter 1 for Darken or 2 for Lighten." << endl;
    }

}

void detectedEdge(Image&image)
{

    //convert to grayscale;

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

    // gaussian blur
    int m[5][5] =
    {
        {1,  4,  7,  4, 1},
        {4, 16, 26, 16, 4},
        {7, 26, 41, 26, 7},
        {4, 16, 26, 16, 4},
        {1,  4,  7,  4, 1}
    };

    vector<vector<int>> k(image.height, vector<int>(image.width, 0));

    for (int j = 2; j < image.height - 2; j++) {
        for (int i = 2; i < image.width - 2; i++) {
            double sum = 0;
            for (int kx= -2;kx<=2;kx++) {
                for (int ky= -2; ky<= 2; ky++) {
                    int px= image(i+kx,j+ ky, 0);
                    sum+= px * m[kx + 2][ky + 2];
                }
            }
            k[j][i] = round(sum / 273);
        }
    }

    vector<vector<int>> gblur(image.height, vector<int>(image.width, 0));
    for (int j = 0; j < image.height; j++) {
        for (int i = 0; i < image.width; i++) {
            gblur[j][i] = k[j][i];
        }
    }

    // sobel;

    int mx[3][3]=
    {
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };

    int my[3][3]=
    {
        {-1,-2,-1},
        {0,0,0},
        {1,2,1}
    };


    vector<vector<int>> ix(image.height, vector<int>(image.width, 0));
    vector<vector<int>> iy(image.height, vector<int>(image.width, 0));


    for(int j=1;j<image.height-1;j++){
        for(int i=1;i<image.width-1;i++){
            int sx=0;
            int sy=0;

            for(int k=-1;k<2;k++){
                for(int l=-1;l<2;l++){
                    int px;
                    px=gblur[j+k][i+l];

                    sx+= px*mx[k+1][l+1];
                    sy+= px*my[k+1][l+1];

                }
            }

            ix[j][i]=sx;
            iy[j][i]=sy;

        }
    }

    vector<vector<unsigned int>> mag(image.height, vector<unsigned int>(image.width, 0));
    for(int j=0;j<image.height;j++){
        for(int i=0;i<image.width;i++){
        mag[j][i] = round(sqrt(ix[j][i]*ix[j][i] + iy[j][i]*iy[j][i]));
        }
    }

    //threshold;
    long long sm=0;
    for (int j=0;j<image.height; j++){
        for (int i=0;i<image.width; i++) {
                sm+=mag[j][i];
        }

    }

    cout<<image.height<<" "<<image.width<<endl;
    unsigned int threshold=round((float) sm / (image.height*image.width)) ;
    threshold=round((float) sm / (image.height*image.width)) *1.7;
    //

    for (int j=0;j<image.height; j++){
        for (int i=0;i<image.width; i++) {
            if(mag[j][i]<=threshold) mag[j][i]=255;
            else mag[j][i]=0;
        }
    }

    for (int j=0;j<image.height; j++){
        for (int i=0;i<image.width; i++)
        {
            for(int k=0;k<3;k++){
                int val = mag[j][i];
                if (val < 0) val = 0;
                if (val > 255) val = 255;
                image(i,j,k) = val;

            }
        }
    }

}

void rotate(Image &image) {
    cout<<"1=> "<<"90 Degree Clockwise\n";
    cout<<"2=> "<<"180 Degree Clockwise\n";
    cout<<"3=> "<<"270 Degree Clockwise\n";
    int no;
    cin>>no;


    switch(no) {

            case 1: {
                // New Dimensions
                int new_width  = image.height;
                int new_height = image.width;
                Image temp(new_width, new_height);

                for (int x = 0; x < image.width; x++) {
                    for (int y = 0; y < image.height; y++) {
                        for (int k = 0; k < image.channels; k++) {
                            int new_x = image.height - 1 - y;
                            int new_y = x;
                            temp(new_x, new_y, k) = image(x, y, k);
                        }
                    }
                }
                swap(image, temp);
                break;
            }
            case 2: {
        Image temp(image.width, image.height);

        for (int x = 0; x < image.width; x++) {
            for (int y = 0; y < image.height; y++) {
                for (int k = 0; k < image.channels; k++) {
                    int new_x = image.width - 1 - x;
                    int new_y = image.height - 1 - y;
                    temp(new_x, new_y, k) = image(x, y, k);
                }
            }
        }
                swap(image, temp);
                break;
    }
        case 3: {
                int new_width  = image.height;
                int new_height = image.width;
                Image temp(new_width, new_height);

                for (int x = 0; x < image.width; x++) {
                    for (int y = 0; y < image.height; y++) {
                        for (int k = 0; k < image.channels; k++) {
                            int new_x = y;
                            int new_y = image.width - 1 - x;
                            temp(new_x, new_y, k) = image(x, y, k);
                        }
                    }
                }
                swap(image, temp);
                break;
        }
            default: {
                cout<<"Invalid Option";
            }

    }
}


void frame(Image &image) {
    cout<<"Choose:"<<endl;
    cout<<"1. Simple Frame"<<endl;
    cout<<"2. Fancy Frame"<<endl;
    int c;
    cin>> c;
    switch(c) {
        case 1: {
            int color_index = image.height / 30;

            for (int i = 0; i < image.width; i++)
                for (int j = 0; j < color_index; j++)
                    image(i,j,0) = 255, image(i,j,1) = 255, image(i,j,2) = 255;

            for (int i = 0; i < image.width; i++)
                for (int j = image.height - color_index; j < image.height; j++)
                    image(i,j,0) = 255, image(i,j,1) = 255, image(i,j,2) =255;

            for (int i = 0; i < color_index; i++)
                for (int j = 0; j < image.height; j++)
                    image(i,j,0) = 255, image(i,j,1) = 255, image(i,j,2) = 255;

            for (int i = image.width - color_index; i < image.width; i++)
                for (int j = 0; j < image.height; j++)
                    image(i,j,0) = 255, image(i,j,1) = 255, image(i,j,2) = 255;
            break;
        }
            case 2: {
            //In Fancy Frame I used the same idea before but in form of if conditions.
            //In The Simple Frame it's just for clarifying the mechanism of work by dividing every side alone

            int base = image.height / 100;
            int gap = base / 2;

            int emerald[3] = {0, 64, 60};
            int bronze[3]  = {205, 127, 50};
            int cream[3]   = {250, 240, 210};

            for (int x = 0; x < image.width; x++) {
                for (int y = 0; y < image.height; y++) {
                    if (x < base || x >= image.width - base ||
                        y < base || y >= image.height - base) {
                        image(x, y, 0) = emerald[0];
                        image(x, y, 1) = emerald[1];
                        image(x, y, 2) = emerald[2];
                        }
                }
            }

            int start1 = base + gap;
            int end_width1 = image.width - (base + gap );
            int end_height1 = image.height - (base + gap);

            for (int x = start1; x < end_width1; x++) {
                for (int y = start1 ; y < end_height1; y++) {
                    if (x < start1 + base || x >= end_width1 - base ||
                        y < start1 + base || y >= end_height1 - base) {
                        image(x, y, 0) = bronze[0];
                        image(x, y, 1) = bronze[1];
                        image(x, y, 2) = bronze[2];
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
                        image(x, y, 0) = cream[0];
                        image(x, y, 1) = cream[1];
                        image(x, y, 2) = cream[2];
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


void purple(Image &image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {

            int r = min(255,int(1.2*image(i, j, 0)));
            int g = min(255,int(0.8*image(i, j, 1)));
            int b = min(255,int(1.2*image(i, j, 2)));
            image(i, j, 0) = r;
            image(i, j, 1) = g;
            image(i, j, 2) = b;

        }
    }
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

void infraredEffect(Image& image)
{
    Image temp = image;

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            int intensity = temp(i, j, 0);
            int inverted = 255 - intensity;

            image(i, j, 0) = 255;
            image(i, j, 1) = inverted;
            image(i, j, 2) = inverted;
        }
    }

}

void sunlight(Image&image)
{
    for(int i=0;i<image.width;i++){
        unsigned int avg=0;
        for(int j=0;j<image.height;j++){
            for(int k=0;k<3;k++){
                avg+=image(i,j,k);
            }
            avg=avg/11;
            // for increase the effect increase (avg/11) to (avg/9)  <- example

                image(i,j,2)-=avg ;
        }
    }

}



void display()
{
    cout<<"1  -> Load a new image\n";
    cout<<"2  -> Gray Scale\n";
    cout<<"3  -> Merge\n";
    cout<<"4  -> Invert\n";
    cout<<"5  -> Blur\n";
    cout<<"6  -> Black & White\n";
    cout<<"7  -> Flip\n";
    cout<<"8  -> Rotate\n";
    cout<<"9  -> Darken & Lighten\n";
    cout<<"10 -> Resize\n";
    cout<<"11 -> Crop\n";
    cout<<"12 -> Add Frame\n";
    cout<<"13 -> Edge detection\n";
    cout<<"14 -> Purple\n";
    cout<<"15 -> Infrared Effect\n";
    cout<<"16 -> Sunlight Effect\n";
    cout<<"17 -> Save the image\n";
    cout<<"0  -> Exit\n";
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
            cout << "Pls Enter The Image Name with Extension: ";
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
    cout << "Pls Enter The Image Name with Extension: ";
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
                cout << "Pls Enter The Image Name with Extension: ";
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
                rotate(image);
                fnum++;
                break;
            }

            case 9:
            {
                darken_lighten(image);
                fnum++;
                break;
            }

            case 10:
            {
                resize(image);
                fnum++;
                break;
            }

            case 11:
            {
                crop_image(image);
                fnum++;
                break;
            }

            case 12:
            {
                frame(image);
                fnum++;
                break;
            }

            case 13:
            {
                detectedEdge(image);
                fnum++;
                break;
            }

            case 14:
            {
                purple(image);
                fnum++;
                break;
            }

            case 15:
            {
                infraredEffect(image);
                fnum++;
                break;
            }

            case 16:
            {
                sunlight(image);
                fnum++;
                break;
            }

            case 17:
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