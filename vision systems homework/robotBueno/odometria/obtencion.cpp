#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main ()
{
	mat A(310,2);
	double t=0.0;
	for(int i=0; i<310; i++)
	{
		if(i>=40)
		{
			A(i,0)=t;
			A(i,1)=(-0.00673574*pow(t*11.3,0)+0.0412766*pow(t*11.3,1)+-0.00802246*pow(t*11.3,2)+0.000430313*pow(t*11.3,3)+-6.87472e-06*pow(t*11.3,4))*10;
			t+=(23/270.0)/11.3;
		}
	}
	A.save("datos.txt", raw_ascii);
	return 0;
}
