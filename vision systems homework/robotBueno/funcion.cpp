#include <iostream>
#include <armadillo>
#include <cmath>

using namespace std;
using namespace arma;

int muestras=1000; //50


int main()
{
	mat A(muestras,2), B(muestras,5), C(muestras,3);
	float theta;
	float T=30.0;
	float d=2.0;
	A(0,0)=0; 
	A(0,1)=0;
	B(0,0)=0;
	B(0,1)=0;
	B(0,2)=T/muestras;
	B(0,3)=0;
	B(0,4)=0;
	C(0,0)=0;
	C(0,1)=0;

	for(double i=1, j=0.002; i<muestras;i+=1, j+=d/muestras)
	{
		A(i,0)=j;
		cout<<j<<endl;
		theta=((2*M_PI)/d)*j;
		A(i,1)=sin(theta)*0.8;

		C(i,0)=(A(i,0)-A(i-1,0))/B(0,2);
		C(i,1)=(A(i,1)-A(i-1,1))/B(0,2);
		//C(i,1)=cos(i);

		B(i,0)=C(i,0);
		//B(i,1)=C(i,1);
		//B(i,0)=sqrt(pow(C(i,0),2)+pow(C(i,1),2));          //////////////////////////
		//B(i,1)=atan(C(i,1)/(C(i,0)))-C(i-1,1);       	////////////////////////
		//B(i,0)=sqrt(pow(A(i,0)-A(i-1,0),2)+pow(A(i,1)-A(i-1,1),2));          //////////////////////////
		B(i,1)=atan((A(i,1)-A(i-1,1))/(A(i,0)-A(i-1,0)))-B(i-1,1);       	////////////////////////
		
		B(i,2)=T/muestras;
		B(i,3)=B(i-1,3)+T/muestras;
		B(i,4)=(B(i,1)-B(i-1,1))/B(0,2);
		C(i,2)=B(i,3);
		
	}
	A.save("datos.txt", raw_ascii);
	B.save("datos2.txt", raw_ascii);
	C.save("datos3.txt", raw_ascii);
	return 0;
}
