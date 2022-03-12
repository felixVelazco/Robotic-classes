#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cstring>
#include <fstream>


using namespace std;
using namespace cv;

int NFOTOS=90;
int MAX_KERNEL_LENGTH=7;

int main (int argc[], char** argv)
{
	string origen, destino;
	Mat src, dst;

	for(int i=0; i<=NFOTOS; i++)
	{
		origen="../../imagenes/build/foto"+to_string(i)+".jpg";
		//origen="../../imagenes/build/foto45.jpg";
		src=imread(origen, IMREAD_COLOR);
		if(!src.data)
		{
			cout<<"No se encontro imagen<<endl";
			return -1;
	}




//Funcion que modifica el brillo o el contraste
	src.convertTo(dst, -1, 3,0);	 //(Mat salida, -1, contraste, brillo)	
	//dst.convertTo(dst, -1, 6,3);	 //(Mat salida, -1, contraste, brillo)	

//Funcion de filtrado
	for(int j=1; j<MAX_KERNEL_LENGTH; j+=2)
	{
		medianBlur(dst, dst, j);
	}
	string median="median"+to_string(i)+".jpg";
	imwrite(median, dst);



	}
	waitKey(0);

	return 0;
}
