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


Image rotate(Image&image)
{
    Image temp=image;

    int rotation_degree;
    
    cout<<"Enter Rotation Degree: ";
    cin>>rotation_degree;

    
    // rotate 270
    if(rotation_degree==270)
    {

        int w=image.width;
        image.width=image.height;
        image.height=w;
        for(int i=0;i<image.width;i++){
            for(int j=0;j<image.height;j++){
                for(int k=0;k<3;k++){

                    image(i,j,k)=temp(j,i,k);
                }
            }
        }
    }



    // rotate 90
    else if(rotation_degree==90)
    {
        int w=image.width;
        image.width=image.height;
        image.height=w;
        for(int i=image.width-1;i>=0;i--){
            for(int j=image.height-1;j>=0;j--){
                for(int k=0;k<3;k++){

                    image(image.width-i,image.height-j,k)=temp(j,i,k);
                }
            }
        }

    }



    // rotate 180
    else if(rotation_degree==180)
    {

        for(int i=image.width-1;i>=0;i--){
            for(int j=image.height-1;j>=0;j--){
                for(int k=0;k<3;k++){

                    image(image.width-i,image.height-j,k)=temp(i,j,k);
                }
            }
        }
    }
    else{
        cout<<"Envalid Degree"<<endl;
        rotate(image);
    }

    return image;
}



int main(){

    Image image("luffy.jpg");
    
    rotate(image);

    image.saveImage("Hello.jpg");

}