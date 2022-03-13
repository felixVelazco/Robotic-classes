
//  Programa 1 : Basicos de Player/Stage, lectura del odometro y un sensor

//  COMPILACION General: 
// g++ -lboost_system -larmadillo -L/usr/local/include/player-3.0 -L/usr/local/include/Stage-3.2 -lplayerc++ -lstage archivo.cpp -o archivo

#define BOOST_SIGNALS_NO_DEPRECATION_WARNING // Stop warning "Boost.Signals" 
#include </usr/local/include/Stage-4.1/stage.hh>
#include </usr/local/include/player-3.0/libplayerc++/playerc++.h>
#include <iostream>
#include <fstream>
#include <armadillo>

using namespace Stg;
using namespace PlayerCc;
using namespace std;
using namespace arma;

int  main()
{
PlayerClient yisus("localhost",6665);
//  PlayerClient yisus("127.0.0.1",6666);
//PlayerClient yisus("189.172.234.65",6667);

	Position2dProxy robot(&yisus,0);
	RangerProxy sonares(&yisus,0);
	RangerProxy lidar(&yisus,1);
	//RangerProxy lidar2(&yisus,2);
	double x,y,a;
	mat Z(2,2), PR(2,1), PG(2,1), T(2,1);
	mat A(300,18), B, s;

	B<<90*3.141593/180.0<<endr
	 <<44*3.141593/180.0<<endr
	 <<12*3.141593/180.0<<endr
	 <<-12*3.141593/180.0<<endr
	 <<-44*3.141593/180.0<<endr
	 <<-90*3.141593/180.0<<endr
	 <<-144*3.141593/180.0<<endr
	 <<144*3.141593/180.0;



//	double theta=-M_PI/2.0;
	double theta=0;
	int i=0;
		
	for(i=0;i<300;i++)
	{
 		yisus.Read();
		x = robot.GetXPos();
		y = robot.GetYPos();
		a = robot.GetYaw();
		int k=0;
		A(i,16)=x;
		A(i,17)=y;

	s<<sonares[0]<<endr
	 <<sonares[1]<<endr
	 <<sonares[2]<<endr
	 <<sonares[3]<<endr
	 <<sonares[4]<<endr
	 <<sonares[5]<<endr
	 <<sonares[6]<<endr
	 <<sonares[7];

	cout<<lidar[0]<<"	"<<lidar[90]<<endl;


		robot.SetSpeed(0.4,0.0);
		for(int j=0;j<8;j++)
		{
			Z<<cos(a)<<-sin(a)<<endr
			 <<sin(a)<<cos(a);
			if(s(j,0)!=5)
			PR<<s(j,0)*cos(B(j,0))<<endr
			  <<s(j,0)*sin(B(j,0));
			else
			PR<<20<<endr
			  <<20;

				T<<-3+x<<endr
				 <<-2+y;

			PG=Z*PR+T;
			//PG=PR;
			//cout<<trans(PR)<<endl;
			A(i,k)=PG(0,0);
			A(i,k+1)=PG(1,0);
			//cout<<A.row(i)<<endl;
			k+=2;

		}			
	}
	//Z.print();
	A.save("sonar2.dat",raw_ascii);

	return 0;
}
