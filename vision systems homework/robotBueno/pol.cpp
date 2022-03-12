#include<iostream>
#include<armadillo>
#include<cmath>

using namespace std;
using namespace arma;


int main ()
{
	mat A(1000,2),B(1000,4);
	float d=10/1000.0, T=180.0;
	A(0,0)=0;
	A(0,1)=1.5+2*A(0,0)+pow(A(0,0),3)/3.0;
	B(0,0)=0;
	B(0,1)=0;
	B(0,3)=0;
	B.col(2).fill(T/1000);
	for(int i=1;i<1000;i++)
	{
		A(i,0)=A(i-1,0)+d;
		A(i,1)=1.5+2*A(i,0)+pow(A(i,0),3)/3.0;

		B(i,0)=sqrt(pow(A(i,0)-A(i-1,0),2)+pow(A(i,1)-A(i-1,1),2))   -B(i-1,0);
		B(i,1)=atan((A(i,1)-A(i-1,1))/(A(i,0)-A(i-1,0)))    -B(i-1,1);
//		B(i,0)=sqrt(pow(A(i,0),2)+pow(A(i,1),2));
//		B(i,1)=atan((A(i,1))/(A(i,0)));

		B(i,3)+=B(i-1,3)+180/1000.0;
	}



	B.save("datos.txt",raw_ascii);

	return 0;
}
