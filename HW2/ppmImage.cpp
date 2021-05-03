#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "pixel.h"
#include "ppmImage.h"









ppmImage::ppmImage( int width , int heigth )
{



    Pixel whitePixel;  //Used to create a white pixel

    vector< Pixel > whiteLine;  //used to create 2d vector which represents pixels of image



    imageWidth = width;

    imageHeigth = heigth;


    maxImageColorDensity=255;  //Maximum value of color densities of all pixels are set to 255




    //canvas vector is filled with white pixels with given width and heigth,pixels are stored as -> canvas[ column_position ][ row_position ]
    //to store image in this format,canvas is transpose form of the image

    for(int columnNum=0 ; columnNum<getImageHeigth() ; columnNum++)
    {
        whiteLine.push_back( whitePixel );
    }


    for(int rowNum=0 ; rowNum<getImageWidth() ; rowNum++)
    {
        canvas.push_back( whiteLine );
    }



}









void ppmImage::operator=(const ppmImage& ppmImageObj)
{


	setMaxImageColorDensity( ppmImageObj.getMaxImageColorDensity() );  //Sets maximum color density of all pixels to the value from source object

	setImageWidth( ppmImageObj.getImageWidth() );  //Sets image width of the image to the value from source object

	setImageHeigth( ppmImageObj.getImageHeigth() );    //Sets image heigth of the image to the value from source object




	for( int rowNumber=0 ; rowNumber<getImageHeigth() ; rowNumber++)
	{

   		for( int columnNumber=0 ; columnNumber<getImageWidth() ; columnNumber++)
    	{
   			canvas[columnNumber][rowNumber] = ppmImageObj.getIndividualPixel( (columnNumber+1),(rowNumber+1) );  //Every pixel from source object is assigned to destination object
		}

   	}


}









void ppmImage::setImageWidth( int newImageWidth )
{

    if( newImageWidth < getImageWidth() )  //Reduces image's width if image is wider than given value
    {

        while( getImageWidth() > newImageWidth )
        {
            imageWidth--;
            canvas.pop_back();
        }

    }


    else  //Increases image's width if image is wider than given value
    {

        vector <Pixel> tempLine;  //Used to fill tempPixel

        Pixel tempPixel;  //Used to


        tempPixel.setMaxPixelColorDensity( maxImageColorDensity );



        while( tempLine.size() < getImageHeigth() )
        {
            tempLine.push_back( tempPixel );
        }


        while( getImageWidth() < newImageWidth )
        {
            imageWidth++;
            canvas.push_back(tempLine);
        }

    }

}










void ppmImage::setImageHeigth( int newImageHeigth )
{

    Pixel tempPixel;


    tempPixel.setMaxPixelColorDensity( maxImageColorDensity );



    if( getImageHeigth() > newImageHeigth )  //Image heigth gets decreased by popping pixels from the end of every column
    {

        for(int columnNum=0 ; columnNum<getImageWidth() ; columnNum++)
        {

            while( canvas[columnNum].size() > newImageHeigth )
            {
                canvas[columnNum].pop_back();
            }

        }

    }



    else  //Image heigth gets increased by pushing pixels to the end of every column
    {

        for(int columnNum=0 ; columnNum<getImageWidth() ; columnNum++)
        {

            while( canvas[columnNum].size() < newImageHeigth )
            {
                canvas[columnNum].push_back( tempPixel );
            }

        }

    }


    imageHeigth = newImageHeigth;


}










void ppmImage::setMaxImageColorDensity( int newMaxImageColorDensity )
{

	maxImageColorDensity = newMaxImageColorDensity;



    //New maximum color density is set for all pixels

	for(int i=0 ; i<canvas.size() ; i++)
	{
		for(int m=0 ; m<canvas[i].size() ; m++)
		{
			canvas[i][m].setMaxPixelColorDensity( newMaxImageColorDensity );
		}
	}


}










void ppmImage::saveImage( string fileName ) const
{

    ofstream saveFile( fileName+".ppm" );

    string line;  //used to fill saveFile,cleared after writing every line


    saveFile << "P3" << endl;

    saveFile << getImageWidth() << " " << getImageHeigth() << endl;

    saveFile << getMaxImageColorDensity() << endl;






	for( int rowNumber=0 ; rowNumber<getImageHeigth() ; rowNumber++)
	{

   		for( int columnNumber=0 ; columnNumber<getImageWidth() ; columnNumber++)  //line is filled by suffixing pixel strings
    	{
            line += canvas[columnNumber][rowNumber].getPixelString() + "      ";
    	}


    	saveFile << line;  //line is written in file

        saveFile << endl;


    	line.clear();  //line string is cleared for next line

	}



	saveFile.close();


}









void ppmImage::loadImage( string fileName )
{

    ifstream loadFile(fileName+".ppm");


    string line;


    int countLine = 1;  //used to reading lines in correct order to set image


    int lineIndex = 0;  //Used for operations on lines,set to '0' for next line when operations on current line is end





    while( getline( loadFile,line) )
    {



        if( countLine == 1 )  //First line of correct file must be "P3" ; otherwise,the file is corrupted
        {
            if( line!="P3" )
            {
                cerr << endl << "File corrupted" << endl;
                exit(1);
            }
        }




        else if( countLine == 2 )  //second line contains width and heigth information of the image
        {

            setImageWidth( stoi(line) );  //first number is width of the image and seperated from the second number with ' ',
                                          //stoi() function reads first line until current character of the string is ' '



            lineIndex = 0;



            while( line[lineIndex] != ' ')  //beginning of the string contains number,after this loop,digits of the number will be ' ',first number gets erased
            {
                line[lineIndex] = ' ';

                lineIndex++;
            }



            setImageHeigth( stoi(line) );  //stoi() function ignores whitespaces at the beginning of the string and reads second number directly

            lineIndex = 0;

        }




        else if( countLine == 3 ) //third line contains a number which is maximum color density of the image
        {
        	setMaxImageColorDensity( stoi(line) );
        }




        else if( countLine > 3 )  //every line is filled from file
        {


            int whichColor = 0;  //Used to choose which color density will be set from the current number of the line

            int columnPosition = 0;  //index of pixel which will be set



            while( lineIndex < line.size() )
            {


            	canvas[columnPosition][countLine-4].setMaxPixelColorDensity( getMaxImageColorDensity() );  //sets current pixel's maximum color density



                //Current color density of current pixel is set to leftmost number of the line


                    if( whichColor == 0 )
                    {
                        canvas[columnPosition][countLine-4].setRedDensity( stoi( line ) );
                        whichColor++;
                    }


                    else if( whichColor == 1 )
                    {
                        canvas[columnPosition][countLine-4].setGreenDensity( stoi( line ) );
                        whichColor++;
                    }


                    //this condition means current pixel is set completely,increments pixel index by one and sets color choice to '0' for next pixel
                    else if( whichColor == 2 )
                    {
                        canvas[columnPosition][countLine-4].setBlueDensity( stoi( line ) );
                        whichColor=0;
                        columnPosition++;
                    }




                //these loops sets all characters of the leftmost number to ' ' , so leftmost number is different
                //every color density value is read from current leftmost number of the line
                while( line[ lineIndex ] != ' ' )
                {
                    line[lineIndex]=' ';
                    lineIndex++;
                }
                while( line[ lineIndex ] == ' ' )
                {
                    lineIndex++;
                }



            }


            lineIndex=0;  //


        }




        countLine++;
    }




    loadFile.close();

}









void ppmImage::printImage() const
{

    string line;  //


	for( int rowNumber=0 ; rowNumber<getImageHeigth() ; rowNumber++)
	{

   		for( int columnNumber=0 ; columnNumber<getImageWidth() ; columnNumber++)  //this loop suffixes pixel dtrings and creates a line
    	{
            line += canvas[columnNumber][rowNumber].getPixelString() + "      ";  //Puts 6 whitespaces at the end of every pixel string
    	}


    	cout << line;  //Prints one line of the image content

    	line.clear();  //Clears line string for next line

    	cout << endl;

	}

}










void ppmImage::printIndividualPixelInfo( int columnPosition , int rowPosition ) const
{

    if( ( columnPosition<1 ) || ( columnPosition>getImageWidth() ) || ( rowPosition<1 ) || ( rowPosition>getImageHeigth() ) )  //Checks if given position parameters are out of image borders
    {
        cerr << endl << " 'printIndividualPixelInfo()' function out of range " << endl;
    }


    else
    {
        cout << endl << "Color values of the pixel at (" << columnPosition << "," << rowPosition << ") :";

        cout << canvas[columnPosition-1][rowPosition-1];  //Prints color information of the pixel at given position
    }

}










void ppmImage::changeIndividualPixelInfo( int columnPosition , int rowPosition , int newRedDensity , int newGreenDensity , int newBlueDensity )
{


	if( ( columnPosition<1 ) || ( columnPosition>getImageWidth() ) || ( rowPosition<1 ) || ( rowPosition>getImageHeigth() ) )  //Checks if given position parameters are out of image borders
    {
        cerr << endl << " 'changeIndividualPixelInfo()' function out of range " << endl;
    }


    else
    {

		canvas[columnPosition][rowPosition].setRedDensity( newRedDensity );

		canvas[columnPosition][rowPosition].setGreenDensity( newGreenDensity );

		canvas[columnPosition][rowPosition].setBlueDensity( newBlueDensity );

	}

}










void ppmImage::swapTwoColorsOfImage( int swap_choice )
{


    bool swapRed = false,
         swapGreen = false,
         swapBlue = false;



    //sets which clors will be swapped according to swap choice

	if( swap_choice == 1 )
	{
        swapRed = true;
        swapGreen = true;
	}

	else if( swap_choice == 2 )
	{
		swapRed = true;
        swapBlue = true;
	}

	else if( swap_choice == 3 )
	{
        swapGreen = true;
        swapBlue = true;
	}




    //Two color densities of all pixels are swapped

    for( int rowNumber=0 ; rowNumber<getImageHeigth() ; rowNumber++)
    {

        for( int columnNumber=0 ; columnNumber<getImageWidth() ; columnNumber++)
        {
            canvas[columnNumber][rowNumber].swapTwoColorsOfPixel( swapRed,swapGreen,swapBlue );
        }

    }



}










void ppmImage::preserveOneColor( bool keepRed , bool keepGreen , bool keepBlue)
{

        //Sets two color density values of all pixels to '0',keeps one of the color densities


		for( int rowNumber=0 ; rowNumber<getImageHeigth() ; rowNumber++)
		{
   			for( int columnNumber=0 ; columnNumber<getImageWidth() ; columnNumber++)
    		{

    				if( keepRed == false )
    				{
           				canvas[columnNumber][rowNumber].setRedDensity(0);
    				}
    				if( keepGreen == false )
    				{
    					canvas[columnNumber][rowNumber].setGreenDensity(0);
    				}
    				if( keepBlue == false )
    				{
    					canvas[columnNumber][rowNumber].setBlueDensity(0);
    				}

    		}
    	}

}










int read_ppm(const string source_ppm_file_name, ppmImage& destination_object)
{

	destination_object.loadImage( source_ppm_file_name );

    return 1;

}










int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object)
{

    source_object.saveImage( destination_ppm_file_name );

    return 1;

}










int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice)
{

	image_object_to_be_modified.swapTwoColorsOfImage( swap_choice );

	return 1;

}










ppmImage single_color( const ppmImage& source , int color_choice )
{

	ppmImage copyObject;

	copyObject = source;


	if( color_choice == 1 )
	{
		copyObject.preserveOneColor( true, false , false);
	}
	else if( color_choice == 2 )
	{
		copyObject.preserveOneColor( false, true , false);
	}
	else if( color_choice == 3 )
	{
		copyObject.preserveOneColor( false , false , true);
	}


	return copyObject;
}









const Pixel ppmImage::getIndividualPixel( int columnPosition , int rowPosition ) const
{

    if( ( columnPosition<1 ) || ( columnPosition>getImageWidth() ) || ( rowPosition<1 ) || ( rowPosition>getImageHeigth() ) )
    {
        cerr << endl << " 'ppmImage::getIndividualPixel()' function out of range " << endl;
        exit(1);
    }


    return canvas[columnPosition-1][rowPosition-1];

}
