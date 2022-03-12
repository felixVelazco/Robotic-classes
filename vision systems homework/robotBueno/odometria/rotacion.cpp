#include<armadillo>
#include<iostream>
#include<cmath>
using namespace std;
using namespace arma;

int main()
{
	mat Z(2,2), PR(2,1), PG(2,1), D(100,4), E(100,2);

	D.load("odometria_vision.txt", arma::raw_ascii);

	for(int j=0;j<100;j++)
	{
		
		int l;
		float a=45;
		l++;
		Z<<cos((a*3.14159/180.0))<<-sin((a*3.14159/180.0))<<endr
		 <<sin((a*3.14159/180.0))<<cos((a*3.14159/180.0));

//		PR<<D(j,0)*cos((-45)*M_PI/180.0)<<endr
//		  <<D(j,0)*sin((-45)*M_PI/180.0);

		PR<<D(j,1)<<endr
		  <<D(j,2);


//				T<<-3+x<<endr
//				 <<-2+y;

		PG=Z*PR;    //+T;
		//PG=PR;
		//cout<<trans(PR)<<endl;
		E(j,0)=PG(0,0);
		E(j,1)=PG(1,0);
		//cout<<A.row(i)<<endl;
	}	
		E.save("Rodom.txt", raw_ascii);

	return 0;



}
