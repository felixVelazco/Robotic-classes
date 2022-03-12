
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
float s=0.0, t=0.0,v=0.0, w=0.0, a=0.0, aw=0.0;
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


///Santo grial
	//v=-0.00183545*pow(t,0)+0.237252*pow(t,1)+-0.175775*pow(t,2)+0.0582888*pow(t,3)+-0.00960175*pow(t,4)+0.000768414*pow(t,5)+-2.38226e-05*pow(t,6);
	//w=-0.00463377*pow(t,-1)+0.602583*pow(t,0)+-0.957071*pow(t,1)+0.411064*pow(t,2)+-0.0786082*pow(t,3)+0.00730788*pow(t,4)+-0.000267701*pow(t,5);
//VERDADERO SANTO GRIAL!!!!! 
	//v=-0.000125641*pow(t,0)+0.210673*pow(t,1)+-0.148105*pow(t,2)+0.0476416*pow(t,3)+-0.00770189*pow(t,4)+0.000609073*pow(t,5)+-1.87408e-05*pow(t,6);
	//w=-0.000285745*pow(t,-1)+0.541591*pow(t,0)+-0.801373*pow(t,1)+0.31896*pow(t,2)+-0.0573122*pow(t,3)+0.0051587*pow(t,4)+-0.000188098*pow(t,5);

s
t=-9.52485e-05*pow(t,0)+0.0601767*pow(t,1)+-0.0148402*pow(t,2)+0.00131259*pow(t,3)+-5.89631e-05*pow(t,4)+1.41528e-06*pow(t,5)+-1.43345e-08*pow(t,6);

v=-4.18802e-05*pow(t,0)+0.0234082*pow(t,1)+-0.00548538*pow(t,2)+0.000588168*pow(t,3)+-3.1695e-05*pow(t,4)+8.35492e-07*pow(t,5)+-8.56919e-09*pow(t,6);
w=0.0601767*pow(t,0)+-0.0296805*pow(t,1)+0.00393778*pow(t,2)+-0.000235853*pow(t,3)+7.0764e-06*pow(t,4)+-8.60073e-08*pow(t,5);


a=0.0234082*pow(t,0)+-0.0109708*pow(t,1)+0.0017645*pow(t,2)+-0.00012678*pow(t,3)+4.17746e-06*pow(t,4)+-5.14151e-08*pow(t,5);
aw=-0.0296805+(0.00393778*2)*pow(t,1)-(0.000235853*3)*pow(t,2)+((7.0764e-06)*4)*pow(t,3)-((8.60073e-08)*5)*pow(t,4);




			robot.SetSpeed(v,w); //4,18
			
			cout<<t<<endl;
			ts=tx+CLOCKS_PER_SEC/1000;
		}
		if(t>30)
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
   //cerr<<"("<<v<<","<<w<<")"<<"  ("<<x<<","<<a<<")"<<endl;
}

return 0;
}
