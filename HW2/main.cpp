//Gebze Technical University
//CSE 241-Object Oriented Programming / 2021 Spring
//Assigment-2

//Student name : Yağız Hakkı Aydın









#include <iostream>
#include <cstring>
#include "pixel.h"
#include "ppmImage.h"



int main( int argc , char** argv )
{



	int choice=argv[1][0];

	string fileName;

	int secArgIndex = 0;



	while( secArgIndex < strlen(argv[2]) )
	{
		fileName += argv[2][secArgIndex];
		secArgIndex++;
	}



	ppmImage ppmImageObject;



	if(choice=='1')
	{
		read_ppm(fileName,ppmImageObject);
		write_ppm("o1",ppmImageObject);
	}
	else if(choice=='2')
	{
		read_ppm(fileName,ppmImageObject);
		swap_channels(ppmImageObject,1);
		write_ppm("o2",ppmImageObject);
	}
	else if(choice=='3')
	{
		read_ppm(fileName,ppmImageObject);
		swap_channels(ppmImageObject,2);
		write_ppm("o3",ppmImageObject);
	}
	else if(choice=='4')
	{
		read_ppm(fileName,ppmImageObject);
		swap_channels(ppmImageObject,3);
		write_ppm("o4",ppmImageObject);
	}
	else if(choice=='5')
	{
		read_ppm(fileName,ppmImageObject);
		ppmImageObject = single_color(ppmImageObject,1);
		write_ppm("o5",ppmImageObject);
	}
	else if(choice=='6')
	{
		read_ppm(fileName,ppmImageObject);
		ppmImageObject = single_color(ppmImageObject,2);
		write_ppm("o6",ppmImageObject);
	}
	else if(choice=='7')
	{
		read_ppm(fileName,ppmImageObject);
		ppmImageObject = single_color(ppmImageObject,3);
		write_ppm("o7",ppmImageObject);
	}





   return 0;


}
