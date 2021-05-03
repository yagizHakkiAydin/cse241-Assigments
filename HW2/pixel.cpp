#include <iostream>
#include <string>
#include "pixel.h"


using namespace std;










Pixel::Pixel(int red,int green,int blue)
{

    maxPixelColorDensity = 255;

    setRedDensity( red );

    setGreenDensity( green );

    setBlueDensity( blue );

}










Pixel::Pixel( const Pixel& pixelObj )
{

    maxPixelColorDensity = pixelObj.getMaxPixelColorDensity();

    setRedDensity( pixelObj.getRedDensity() );

    setGreenDensity( pixelObj.getGreenDensity() );

    setBlueDensity( pixelObj.getBlueDensity() );

}





void Pixel::operator=( const Pixel& pixelObj)
{

    setRedDensity( pixelObj.getRedDensity() );

    setGreenDensity( pixelObj.getGreenDensity() );

    setBlueDensity( pixelObj.getBlueDensity() );

    setPixelString();

};







void Pixel::setRedDensity( int newRedDensity )
{

    if(  ( newRedDensity > getMaxPixelColorDensity() )  ||  ( newRedDensity < 0 )  )  //checks if changing red density with given value is out of max and min color density
    {
        cerr << endl << "setRedDensity() function out of range " << endl;
        exit( 1 );
    }

    else
    {
        redDensity = newRedDensity;
        setPixelString();
    }

}







void Pixel::setGreenDensity( int newGreenDensity )
{

    if(  ( newGreenDensity > getMaxPixelColorDensity() )  ||  ( newGreenDensity < 0 )  )  //checks if changing green density with given value is out of max and min color density
    {
        cerr << endl << "setGreenDensity() function out of range " << endl;
        exit(1);
    }
    else
    {
        greenDensity = newGreenDensity;
        setPixelString();
    }
}








void Pixel::setBlueDensity(int newBlueDensity)
{

    if(  ( newBlueDensity > getMaxPixelColorDensity() )  ||  ( newBlueDensity < 0 )  )  //checks if changing blue density with given value is out of max and min color density
    {
        cerr << endl << "setBlueDensity() function out of range " << endl;
        exit(1);
    }

    else
    {
        blueDensity = newBlueDensity;
        setPixelString();
    }
}









void Pixel::setPixelString()  //uses "to_string()" to cast color densities to strings , sets pixel string with splicing color densities in orded --> red,green,blue
{

    pixelString.clear();


    pixelString += to_string( getRedDensity() );

    pixelString += " ";


    pixelString += to_string( getGreenDensity() );

    pixelString += " ";


    pixelString += to_string( getBlueDensity() );

}




void Pixel::setMaxPixelColorDensity( int newMaxPixelColorDensity )
{

    if(maxPixelColorDensity>255)  //Ensures that max color density won't be higher than 255,sets higher values to 255
    {
        maxPixelColorDensity = 255;
    }

    else if(maxPixelColorDensity<0)  //Ensures that min color density won't be less than 0,sets less values to 0
    {
        maxPixelColorDensity = 0;
    }

    else
    {
        maxPixelColorDensity = newMaxPixelColorDensity;
    }




    if(  getRedDensity() > getMaxPixelColorDensity()  )   //If red density of pixel is above max density,it is reduced to value of max density
    {
        setRedDensity( getMaxPixelColorDensity()  );
    }

    if(  getGreenDensity() > getMaxPixelColorDensity()  )   //If green density of pixel is above max density,it is reduced to value of max density
    {
        setGreenDensity( getMaxPixelColorDensity() );
    }

    if(  getBlueDensity() > getMaxPixelColorDensity()  )    //If blue density of pixel is above max density,it is reduced  to value of max density
    {
        setBlueDensity( getMaxPixelColorDensity()  );
    }

}








istream& operator >>(istream &istObj,Pixel &pixelObj)
{

    int  newRedDensity=0,
         newGreenDensity=0,
         newBlueDensity=0;



    istObj >> newRedDensity >> newGreenDensity >> newBlueDensity;  //gets user input to set color densities



    pixelObj.setRedDensity( newRedDensity );

    pixelObj.setGreenDensity( newGreenDensity );

    pixelObj.setBlueDensity( newBlueDensity );



    return istObj;

}








ostream& operator <<( ostream &ostObj , const Pixel &pixelObj )
{

     ostObj  << endl << "Red density of the pixel -->" << pixelObj.getRedDensity() << endl
                     << "Green density of the pixel -->" << pixelObj.getGreenDensity() << endl
                     << "Blue density of the pixel -->" << pixelObj.getBlueDensity() << endl;



    return ostObj;

}









const Pixel Pixel::operator +( const Pixel &pixelObj ) const
{

    Pixel tempPixelObject;  //A temporary pixel object, it is created to be returned


    int tempRedDensity,   //
        tempGreenDensity, //Temporary variables,keeps sum of two pixel's color densities
        tempBlueDensity;  //






    tempRedDensity = getRedDensity() + pixelObj.getRedDensity();

    if( tempRedDensity > maxPixelColorDensity)
    {
        tempRedDensity = maxPixelColorDensity;
    }




    tempGreenDensity = getGreenDensity() + pixelObj.getGreenDensity();

    if( tempGreenDensity > maxPixelColorDensity )
    {
        tempGreenDensity = maxPixelColorDensity;
    }




    tempBlueDensity = getBlueDensity() + pixelObj.getBlueDensity();

    if( tempBlueDensity > maxPixelColorDensity )
    {
        tempBlueDensity = maxPixelColorDensity;
    }




    tempPixelObject.setRedDensity( tempRedDensity );

    tempPixelObject.setGreenDensity( tempGreenDensity );

    tempPixelObject.setBlueDensity( tempBlueDensity );



    return tempPixelObject;

}









const Pixel Pixel::operator -( const Pixel &pixelObj ) const
{

    Pixel tempPixelObject;


    int tempRedDensity,
        tempGreenDensity,
        tempBlueDensity;




    tempRedDensity = getRedDensity() - pixelObj.getRedDensity();

    tempGreenDensity = getGreenDensity() - pixelObj.getGreenDensity();

    tempBlueDensity = getBlueDensity() - pixelObj.getBlueDensity();




    if( tempRedDensity < 0)
    {
        tempRedDensity = 0;
    }

    if( tempGreenDensity < 0 )
    {
        tempGreenDensity = 0;
    }

    if( tempBlueDensity < 0 )
    {
        tempBlueDensity = 0;
    }




    tempPixelObject.setRedDensity( tempRedDensity );

    tempPixelObject.setGreenDensity( tempGreenDensity );

    tempPixelObject.setBlueDensity( tempBlueDensity );




    return tempPixelObject;

}










void Pixel::swapTwoColorsOfPixel(bool swapRed , bool swapGreen , bool swapBlue)
{


    int temp;  //Temporary integer,used to swapping two color density values of the pixel



    if( (swapRed==false) && (swapGreen==true) && (swapBlue==true) )
    {

        temp=getGreenDensity();

        setGreenDensity( getBlueDensity() );

        setBlueDensity( temp );

    }




    else if( (swapRed==true) && (swapGreen==false) && (swapBlue==true) )
    {

        temp=getRedDensity();

        setRedDensity( getBlueDensity() );

        setBlueDensity( temp );

    }




    else if( (swapRed==true) && (swapGreen==true) && (swapBlue==false) )
    {

        temp=getRedDensity();

        setRedDensity( getGreenDensity() );

        setGreenDensity( temp );

    }

}
