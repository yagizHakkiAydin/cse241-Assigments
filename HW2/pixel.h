#ifndef PIXEL_H
#define PIXEL_H

#include<iostream>
#include<string>


using namespace std;




class Pixel
{
    public:

        Pixel() : Pixel(255,255,255) {/*Intentionally empty*/}  //Default constructor,initializes default pixel as white pixel

        Pixel(int red,int green,int blue);  //Constructor,takes red,green and blue color densities as parameter and initializes default pixel,uses setters to check max and min densities

        Pixel( const Pixel& pixelObj );  //Constructor,takes another pixel object reference as parameter to initialize pixel

        void operator=( const Pixel& pixelObj);  //Copy assigment operator



        const int getRedDensity() const{ return redDensity; }  //Returns red color density of the pixel

        const int getGreenDensity() const{ return greenDensity; }  //Returns green color density of the pixel

        const int getBlueDensity() const{ return blueDensity; }  //Returns blue color density of the pixel

        const int getMaxPixelColorDensity() const{ return maxPixelColorDensity; }  //Returns maximum limit of color density of the pixel

        const string getPixelString() const{ return pixelString; }  //Returns a string which identifies pixel ; for example , white pixel is identified as --> "255 255 255"



        void setRedDensity(int newRedDensity);      //
                                                    //
        void setGreenDensity(int newGreenDensity);  //Color density setter functions,also pixelString is set after changing color densities
                                                    //
        void setBlueDensity(int newBlueDensity);    //


        void setMaxPixelColorDensity(int newmaxPixelColorDensity);




        friend istream& operator >>(istream &istObj , Pixel &pixelObj);  //Gets three integers in order "r,g,b" and sets pixel

        friend ostream& operator <<(ostream &ostObj , const Pixel &pixelObj);  //Prints information about pixel

        const Pixel operator +( const Pixel &pixelObj ) const;  //Adds two pixel objects

        const Pixel operator -( const Pixel &pixelObj ) const;  //Subtracts two pixel objects


        void swapTwoColorsOfPixel(bool red , bool green , bool blue);  //Swaps color densities of the pixel,two of parameters must be "true"






    private:

        int redDensity,       //
            greenDensity,    // Color densities of te pixel
            blueDensity;    //



        int maxPixelColorDensity;  //Maximum value of the color densities of te pixel



        string pixelString;  //The string which identifies pixel ; for example , white pixel is identified as --> "255 255 255"



        void setPixelString();  //Sets pixelString private member data,only needed in color density setter functions



};


#endif
