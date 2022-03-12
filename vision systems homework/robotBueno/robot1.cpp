
//  Programa 1 : Basicos de Player/Stage, lectura del odometro y un sensor

//  COMPILACION General: 
// g++ -lboost_system -larmadillo -L/usr/local/include/player-3.0 -L/usr/local/include/Stage-4.3 -lplayerc++ -lstage archivo.cpp -o archivo

#define BOOST_SIGNALS_NO_DEPRECATION_WARNING // Stop warning "Boost.Signals" 
#include </usr/local/include/Stage-4.1/stage.hh>
#include </usr/local/include/player-3.0/libplayerc++/playerc++.h>
#include <iostream>
#include <fstream>
#include <armadillo>
#include <cmath>
#include <chrono>
#include <thread>
#include <time.h>


using namespace Stg;
using namespace PlayerCc;
using namespace std;
using namespace arma;
using namespace std::chrono;
using namespace std::this_thread;


mat A(4,3);
mat B(4,4);
float v=0.0, w=0.0;
float pi=3.141593;

float angulo(float x1, float x2, float y1, float y2)
{
float a;
if(x2>x1)
	a=atan((y2-y1)/(x2-x1));
else
	if(x2<x1)
		{a=-pi+atan((y2-y1)/(x2-x1));}
	else
		if(y2>y1)
			a=pi/2.0;
		else
			a=-pi/2.0;
return a;

}

float interpolacion(int k, float t)
{
	float b=0.0;
	float d=0.0;

	for(int i=0; i<k; i++)
	{
		float a=1.0;
		float c=1.0;
		for(int j=0;j<k;j++)
		{
			if(j!=i)
			{
				a*=((t-A(j,0))/(A(i,0)-A(j,0)));
				c=a;
			}
		}
		a*=A(i,1);
		c*=A(i,2);
		b+=a;
		d+=c;
	}
	v=d;
	w=b;
//	cout<<"v="<<v;
//	cout<<"   w="<<w<<endl;
}

float derivada(int b)
{
	float t=0.0;
	A(0,0)=0;
	A(0,1)=0;
	A(0,2)=0;
	for(int i=0;i<b-1;i++)
	{
		t+=B(i+1,0);
		A(i+1,0)=t;
		A(i+1,1)=(B(i+1,1)-B(i,1))/B(i+1,0);
		A(i+1,2)=sqrt(pow(B(i+1,2)-B(i,2),2)+pow(B(i+1,3)-B(i,3),2))/B(i+1,0);
		cout<<"("<<A(i,2)<<")"<<endl;
	}
}





int  main()
{
PlayerClient yisus("localhost",6665);
//  PlayerClient yisus("127.0.0.1",6666);
//PlayerClient yisus("189.172.234.65",6667);

  Position2dProxy robot(&yisus,0);
  RangerProxy sonares(&yisus,0);
  double x=0, y=0, a,r, vel;
  double s0,s1,s2,s3,s4,s5,s6,s7;
  double t0=90,t1=41,t2=15,t3=-15,t4=-41,t5=-90,t6=-145,t7=145;
  double x1,y1;
  int c,b;
  float t=0.0;
  int j=0,z=0;
  float theta;
  float tcpu=0;
//   time_t now = time(0);


//SE DEFINE LA MATRIZ B
	B<<0	<<0.0		<<0	<<0	<<endr
	 <<2	<</*0.2617*/30.96*pi/180.0	<<5	<<3.0	<<endr
	 <<4.5	<</*-0.349*/-50.19*pi/180.0	<<10.0	<<-3.0	<<endr
	 <<3.5	<</*0.6981*/63.43*pi/180.0	<<15.0	<<7.0;

	b=B.n_rows;


//	derivada(b);
	A.print();
	A<<0<<0<<0<<endr
	 <<2<</*0.1308*/0.27015<<2.9155<<endr
	 <<6.5<</*-0.1357*/-0.3147<<1.7356<<endr
	 <<10<</*0.2992*/0.5665<<3.1499;
	A.print();
	c=A.n_rows;

t=0.0;
clock_t tx,ts;
ts=clock()+CLOCKS_PER_SEC/1000.0;
while(t<=10)
{

   yisus.Read();
   x = robot.GetXSpeed();
   y = robot.GetYSpeed();
   a = robot.GetYawSpeed();
 
//	interpolacion(c,t);
	
	//robot.SetSpeed(0.5,w);
	//v=(0.034946*pow(t,3)-0.561642*pow(t,2)+2.4411*t)/1000.0;
	//w=(0.004211*pow(t,3)-0.05497*pow(t,2)+0.15852*t)/1000.0;
//	v=-5.1724*pow(10,-5)+6.24*pow(10,-5)*t-2.4801*pow(10,-9)*pow(t,2);
//	w=1.2669*pow(10,-2)-2.126*pow(10,-4)*t+8.8818*pow(10,-7)*pow(t,2);
	
//	sleep_for (milliseconds(1000));
//	t+=1;
	tcpu=0.0;



	for(;;)
	{

		if((tx=clock())>=ts)
		{



			t+=1/1000.0;




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//v=-0.00552001*pow(t,0)+1.87777*pow(t,1)+-3.43749*pow(t,2)+2.91268*pow(t,3)+-1.43541*pow(t,4)+0.444575*pow(t,5)+-0.0883444*pow(t,6)+0.0111816*pow(t,7)+-0.000868791*pow(t,8)+3.7722e-05*pow(t,9)+-7.00513e-07*pow(t,10);
//w=-0.00504066*pow(t,0)+2.10242*pow(t,1)+-4.66448*pow(t,2)+5.03204*pow(t,3)+-3.05379*pow(t,4)+1.09976*pow(t,5)+-0.243717*pow(t,6)+0.0335568*pow(t,7)+-0.00279594*pow(t,8)+0.000129026*pow(t,9)+-2.53072e-06*pow(t,10);
//w=-0.00504066*pow(t,-1)+2.10242*pow(t,0)+-9.32896*pow(t,1)+15.0961*pow(t,2)+-12.2152*pow(t,3)+5.49882*pow(t,4)+-1.4623*pow(t,5)+0.234897*pow(t,6)+-0.0223675*pow(t,7)+0.00116124*pow(t,8)+-2.53072e-05*pow(t,9);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//v=-1.11112e-11*pow(t,0)+0.1*pow(t,1)+1.5299e-08*pow(t,2)+-2.03835e-08*pow(t,3)+1.35044e-08*pow(t,4)+-5.10461e-09*pow(t,5)+1.17185e-09*pow(t,6)+-1.66358e-10*pow(t,7)+1.42683e-11*pow(t,8)+-6.77536e-13*pow(t,9)+1.36751e-14*pow(t,10);
//w=-3.05904e-07*pow(t,-1)+0.628194*pow(t,0)+0.00107011*pow(t,1)+-0.126512*pow(t,2)+0.00259243*pow(t,3)+0.00261693*pow(t,4)+0.000486551*pow(t,5)+-0.000151482*pow(t,6)+1.1471e-05*pow(t,7)+-2.75068e-07*pow(t,8)+-4.97206e-10*pow(t,9);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

v=-1.11112e-11*pow(t,0)+0.1*pow(t,1)+1.5299e-08*pow(t,2)+-2.03835e-08*pow(t,3)+1.35044e-08*pow(t,4)+-5.10461e-09*pow(t,5)+1.17185e-09*pow(t,6)+-1.66358e-10*pow(t,7)+1.42683e-11*pow(t,8)+-6.77536e-13*pow(t,9)+1.36751e-14*pow(t,10);
w=0.000313935*pow(t,-1)+1.38051*pow(t,0)+-1.03297*pow(t,1)+1.30507*pow(t,2)+-2.24279*pow(t,3)+1.27425*pow(t,4)+-0.32143*pow(t,5)+0.0402317*pow(t,6)+-0.00239835*pow(t,7)+4.7431e-05*pow(t,8)+5.31998e-07*pow(t,9);

			robot.SetSpeed(v,w);
			//robot.SetSpeed(v*1.1,w*1.7); 
			
			cout<<t<<endl;
			ts=tx+CLOCKS_PER_SEC/1000;
		}
		if(t>12)
			return 0;
//	cerr<<tx<<"   "<<ts<<endl;
	}

//	while(tcpu<=0.1)
//	{
//		v=0.034946*pow(t,3)-0.561642*pow(t,2)+2.4411*t;
//		w=0.004211*pow(t,3)-0.05497*pow(t,2)+0.15852*t;
//		robot.SetSpeed(v,w);
//		tcpu=;									//FALTA EL TIEMPO
//		cout<<tcpu<<endl;
//	}
//	t+=0.1;

   //cout<<"("<<x<<","<<y<<","<<a<<") "<<endl;
//   cerr<<"("<<v<<","<<w<<")"<<"  ("<<x<<","<<a<<")"<<endl;
}

return 0;
}
