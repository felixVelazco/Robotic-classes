#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <armadillo>

using namespace std;
using namespace cv;
//using namespace arma;

int MAX_KERNEL_LENGTH = 3;
int threshold_type = 0;
int q=0;

int main(int argc[], char** argv)
{
	Mat src, dst;
	string origen, destino;
	arma::mat A(310,2), B(310,2), C(310,2), D(100,2), E(310,2), F(310,2), G(310,2), ERRX(310,2), ERRY(310,2);
	double k=0;

		D.load("/home/felix/Documents/8vo\ semestre/robotica/vision/Tarea\ 6/robotBueno/odometria/Rodom.txt");

RNG rng(12345);

	//Ciclo para leer todas las imagenes
	for(int i=0; i<=309; i++)
	{
		origen="../../imagenes/foto"+to_string(i)+".jpg";
		//origen="../../imagenes/foto170.jpg";  //10 y 78
		src=imread(origen, IMREAD_COLOR);

		if(!src.data)
		{
			cout<<"Imagen "<<to_string(i)<<" no encontrada"<<endl;
			return -1;
		}

	
	
	src.convertTo(dst,-1, 3,10);
	

	for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
	{
		medianBlur ( dst, dst, i );
	}

		string median="median"+to_string(i)+".jpg";
		imwrite(median, dst);


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*
	cvtColor(dst, dst, COLOR_BGR2GRAY);
	equalizeHist(dst, dst);
	string equalizador="equalizador"+to_string(i)+".jpg";
	imwrite(equalizador, dst);
	cvtColor(dst, dst, COLOR_GRAY2BGR);
	string equalizador2="equalizador_color"+to_string(i)+".jpg";
	imwrite(equalizador2, dst);*/
/*
	Mat bgr_image=dst;
	Mat lab_image;
	cvtColor(bgr_image, lab_image, CV_BGR2Lab);
	vector<Mat> lab_planes(3);
	split(lab_image, lab_planes);  // now we have the L image in lab_planes[0]

	// apply the CLAHE algorithm to the L channel
	Ptr<CLAHE> clahe = createCLAHE();
	clahe->setClipLimit(4);
	Mat dst;
	clahe->apply(lab_planes[0], dst);

	// Merge the the color planes back into an Lab image
	dst.copyTo(lab_planes[0]);
	merge(lab_planes, lab_image);

   // convert back to RGB
	Mat image_clahe;
	cvtColor(lab_image, dst, CV_Lab2BGR);


	
	for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
	{
		medianBlur ( dst, dst, i );
	}
	string equalizador="equalizador"+to_string(i)+".jpg";
	imwrite(equalizador, dst);
*/

 ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

	vector<Mat> rgbChannels(3);
	split(dst, rgbChannels);
	namedWindow("median",1);imshow("median", dst);

	// Show individual channels
	Mat g, fin_img;
	g = Mat::zeros(Size(dst.cols, dst.rows), CV_8UC1);
     	

	Mat verde;
	verde=rgbChannels[1];	
	threshold( rgbChannels[1], verde, 240, 250, threshold_type );	
	namedWindow("verde",1);imshow("verde", verde);


/////////////////////////////////////////////////////////////////
	Mat rojo;
	rojo=rgbChannels[2];
	threshold( rgbChannels[2], rojo, 240, 250, threshold_type ); //////// 248, 255
	namedWindow("rojo",1);imshow("rojo", rojo);

/////////////////////////////////////////////////////////////////////
	Mat azul;
	azul=rgbChannels[0];
	threshold( rgbChannels[0], azul, 170, 250, threshold_type ); //////// 248, 255
	namedWindow("azul",1);imshow("azul", azul);


/////////////////////////////////////////////////////////////////
	Mat r;
	bitwise_and(rojo,verde,r);
	//threshold( r, r, 240, 255, threshold_type );
	namedWindow("pudin",1);imshow("pudin", r);


 	// Showing Yellow Channel
	// G and B channels are kept as zero matrix for visual perception
	{
		vector<Mat> channels;
		//channels.push_back(g);			
		channels.push_back(rgbChannels[0]);
		channels.push_back(rgbChannels[1]);
		channels.push_back(rgbChannels[2]);
 
	/// Merge the three channels
		merge(channels, fin_img);
		namedWindow("Y",1);imshow("Y", fin_img);
	string y="y"+to_string(i)+".jpg";
	imwrite(y, fin_img);
	}


	float morph_size = 4; /////////////////////////AQUI 7
	Mat kernel = getStructuringElement(MORPH_RECT, Size(2*morph_size+1, 2*morph_size+1), Point(morph_size, morph_size) );

	erode(r, r, kernel);

	morph_size = 4;//////////////////////////////AQUI 9
	kernel = getStructuringElement(MORPH_RECT, Size(2*morph_size+1, 2*morph_size+1), Point(morph_size, morph_size) );
	dilate(r, r, kernel);


	string filtro="filtrado"+to_string(i)+".jpg";
	imwrite(filtro, r);


	//Segmentacion

	Mat labels,stats, centroids;	//	vector<Point2f> centroids() );
	int nLabels = connectedComponentsWithStats(r, labels, stats, centroids,8, CV_16U);
		
//	namedWindow("algo", CV_WINDOW_AUTOSIZE);
//	imshow("algo",labels[1]);

	int z=0;
	for(z=0; z<nLabels;z++)
	{
		int area=0, temp=0;
		area=stats.at<int>(z,4);
		if(area>150 && area<2800)
			break;
		//cout<<stats<<endl;
	}
	cout<<"es este"<<z<<endl;
	float x= centroids.at<double>(z,0);
	float y= centroids.at<double>(z,1);
	cout<<nLabels<<endl;
//	cout<<centroids<<endl;
	float x1=0.0, y1=0.0;
	x1=((x-320)*2.4518)/640.0;
	y1=((-y+240)*1.8266)/480.0;

	A(i,0)=x1;
	A(i,1)=y1;

	B(i,0)=x;
	B(i,1)=y;

	
	float x2=0;
	float y2=0;

//	for(double k=0.0; k<=2.0; k+=2/310.0)
//	{
		int a=0, b=0;
	if(i>=40)
	{
		x2=k;
		y2=-sin(((2*3.1415)/2)*k+3.1415)*0.8;		
		
		k+=2/270.0;		
//		cout<<endl<<"x y y"<<endl;
//		cout<<x2<<"	"<<y2<<endl;

		a=((x2)*640)/2.4518+60;
		b=-((y2-0.9133)*480)/1.8266;
		//cout<<a<<"	"<<b<<endl;
		C(i-40,0)=a;
		C(i-40,1)=b;

		F(i-40,0)=i/2.0;
		//F(i-40,1)=-(abs(sqrt(pow(C(i-40,1)-B(i,1),2)+pow(C(i-40,0)-B(i-40,0),2)))-240);//(C(i-40,0)-B(i,0)));
		//F(i-40, 1)=/*-*/(sqrt(pow((x1)-(x2-1),2)+pow(y1-y2,2))/**150-440*/) /sqrt(pow(x1,2)+pow(y1,2)) ;    ///GLOBAL VS REFERENCIA           //LE CAMBIE DE SIGNO AL PRINCIPIO y el 150
		F(i-40, 1)=-(sqrt(pow((x1)-(x2-1),2)+pow(y1-y2,2))*150-440);

		G(q,0)=i/2.0;
		G(q,1)=-(sqrt(pow((x1)-(D(q,0)-1.1356),2)+pow(y1-(D(q,1)+0.0459),2))*150-440); //150 y 330
		//G(q,1)=-(sqrt(pow((x1)-(D(q,0)-1.1356),2)+pow(y1-(D(q,1)+0.0459),2))*150-440) /sqrt(pow(x1,2)+pow(y1,2))        ; //150 y 330
		//ERRX(0).fill(i);
		//ERRX(i-40,1)=240;
		

	}



		//float x3=0, y3=0;
	if(i>=40&&q<140)
	{

		int a=0, b=0;
		if(i%3==0)
			q++;
			a=((D(q,0))*640)/2.4518+23;
			b=-(((D(q,1)-0.9133)*480)/1.8266)-12;
		cout<<a<<"	"<<b<<endl;
		E(i,0)=a;
		E(i,1)=b;

//		cout<<"C "<<G(i-40,0)<<"	"<<G(i-40,1)<<endl;

//		cout<<"error "<<i-40<<"	"<<F(i-40,1)<<endl;

		putText(src, "ODOMETER("+to_string(D(q,0)-1.1356)+" , "+to_string(D(q,1)+0.0459)+")", Point(380,90), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0,255,0), 1, LINE_AA);

	}




		Mat mask, color, final;
	for(int k=2;k<nLabels; k++)
	{

		inRange(labels, Scalar(k), Scalar(k+3), mask);
		cvtColor(labels, color, COLOR_GRAY2BGR);
		color.setTo(Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)), mask);
		//color.setTo(Scalar(rng.uniform(255,255),rng.uniform(255,255),rng.uniform(255,255)), mask);
		color.copyTo(final, mask);
		//	cvtColor(final, final, CV_BGR2GRAY);
		//	threshold( final, final, 100,255,THRESH_BINARY );		

		//bitwise_not(final, final);
	}

	namedWindow("segmented", CV_WINDOW_AUTOSIZE);
	imshow("segmented", labels);
	destino="labels"+to_string(i)+".jpg";
	imwrite(destino, final);

		




	circle(src, Point(x,y), 4, Scalar(0,0,255), -1, 8, 0);
	putText(src, "GLOBAL VISION("+to_string(x1)+" , "+to_string(y1)+")", Point(380,30), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(255,0,255), 1, LINE_AA);
	putText(src, "REFERENCE("+to_string(x2-1)+" , "+to_string(y2)+")", Point(380,60), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(255,0,0), 1, LINE_AA);
//	if(i>=40&&i<140)

	for(int l=0; l<i; l++)
	{
		//cout<<A(l,0)<<endl;
		circle(src, Point(B(l,0),B(l,1)), 3, Scalar(255,0,255), -1, 8, 0);
		circle(src, Point(C(l,0),C(l,1)), 3, Scalar(255,0,0), -1, 8, 0);
		circle(src, Point(E(l,0),E(l,1)), 3, Scalar(0,255,0), -1, 8, 0);
		//Graficas de error 
		circle(src, Point(F(l,0),F(l,1)), 1, Scalar(255,0,0), -1, 8, 0);
		circle(src, Point(G(l,0),G(l,1)), 1, Scalar(0,255,0), -1, 8, 0);
		//ejes
		line(src, Point(17,440), Point(220,440), Scalar(0,0,0), 1.5, 8, 0);
			putText(src, "t", Point(225,440), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0,0,0), 1, LINE_AA);
		line(src, Point(17,440), Point(17,360), Scalar(0,0,0), 1.5, 8, 0);
			putText(src, "E", Point(17,355), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0,0,0), 1, LINE_AA);

		putText(src, "Absolute error", Point(50,460), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0,0,0), 1, LINE_AA);
//		putText(src, "-Reference VS Odometer", Point(30,440), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0,255,0), 1, LINE_AA);
//		putText(src, "-Reference VS Global vision", Point(30,460), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(255,0,255), 1, LINE_AA);
		//line(src, Point(240,l), 3, Scalar(0,0,0), -1, 8, 0);
				
	}







	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", src);




	destino="mejora"+to_string(i)+".jpg";
	imwrite(destino, src);

	}
	A.save("vision.txt", arma::raw_ascii);
	F.save("ErRvsV.txt", arma::raw_ascii);
	G.save("ErOvsV.txt", arma::raw_ascii);
	waitKey(0);

	return 0;
}
