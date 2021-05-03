#ifndef PPMIMAGE_H
#define PPMIMAGE_H


#include <iostream>
#include <vector>
#include <string>
#include "pixel.h"



class ppmImage
{


    public:

        ppmImage( ) : ppmImage( 512,512 ) { /*Intentionally Empty*/ }  //Default constructor,initializes 512x512 white image defaultly

        ppmImage( int width , int height );  //Constructor,initializes white image with given dimention informations

        ppmImage( string ppmFileName ){ loadImage( ppmFileName ); }  //Constructor,initializes image by loading the file with given name


        void operator=( const ppmImage& ppmImageObj);  //Assigns one ppmImage object to another



        const int getImageWidth() const{ return imageWidth; }  //Returns width of image

        const int getImageHeigth() const{ return imageHeigth; }  //Returns heigth of image

        const int getMaxImageColorDensity() const{ return maxImageColorDensity; }  //Returns maximum color density that any pixel of the image




        void setImageWidth( int newImageWidth );  //Sets image width,adjusts canvas vector

        void setImageHeigth( int newImageHeigth );  //Sets image heigth,adjusts canvas vector

        void setMaxImageColorDensity( int newMaxImageColorDensity );  //Sets maximum color density of all pixels,reduces densities of pixels if it's necessary



        void saveImage( string fileName ) const;  //Creates a new .ppm file with given name and saves te image. ".ppm" extension is automatically added to given filename

        void loadImage( string fileName );  //Loads image from ppm image with given name. ".ppm" extension is automatically added to given filename


        void printImage() const;  //Prints image to the console




        void printIndividualPixelInfo( int columnPosition , int rowPosition ) const;  //Prints information of the pixel at given position


        void changeIndividualPixelInfo( int columnPosition , int rowPosition , int newRedDensity , int newGreenDensity , int newBlueDensity );  //Prints information of the pixel at 																		      //given position with given color values



        void swapTwoColorsOfImage( int choice );  //Swaps two color density values of all pixels.()

        void preserveOneColor( bool keepRed , bool keepGreen , bool keepBlue);  //Sets two color density values of all pixels to '0', choice 1->Red,Green ; choice 2->Red,Blue ; choice 3->Green,Blue

        const Pixel getIndividualPixel( int columnPosition , int rowPosition ) const;  //Returns a copy of pixel object which is at given position






    private:

        int imageWidth,imageHeigth;

        vector< vector<Pixel> > canvas;  //2d vector of pixel objects pixels are stored as -->  canvas[width][heigth]

        int maxImageColorDensity;


};













// returns 1 if the operation is successful. otherwise, returns 0.
// reads ppm data from file named as source_ppm_file_name. stores data in destination_object
int read_ppm(const string source_ppm_file_name, ppmImage& destination_object);









// returns 1 if the operation is successful. otherwise, returns 0.
// writes ppm data from source_object to the file named destination_ppm_file_name.
int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object);












//this function swaps the color values of every pixel in a given ppm image.
//this function does not create a new object but modifies the given one.
//if swap_choice is 1: swaps red and green
//if swap_choice is 2: swaps red and blue
//if swap_choice is 3: swaps green and blue
//if swap_choice is not 1, 2 or 3: no swaps (this does not mean that the operation is not successful.
//the function should return 1 in this case if everything is normal)
// returns 1 if the operation is successful. otherwise, returns 0.
int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice);









//creates and returns a copy of a new ppmImage object which stores only one color at each pixel.
//This simply takes the source and copies only one color information and stores it in a new object.
//The other color channels are simply going to be zeros.
//if color_choice is 1: red channel is preserved
//if color_choice is 2: green channel is preserved
//if color_choice is 3: blue channel is preserved
ppmImage single_color(const ppmImage& source, int color_choice);





#endif
