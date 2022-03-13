
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
  double x, y, a,r;
  double s0,s1,s2,s3,s4,s5,s6,s7;
  double t0=90,t1=41,t2=15,t3=-15,t4=-41,t5=-90,t6=-145,t7=145;
  double x1,y1;
  mat A(400,18);
  mat B(8,1);
   B<<90*3.141593/180.0<<endr
   <<44*3.141593/180.0<<endr
   <<12*3.141593/180.0<<endr
   <<-12*3.141593/180.0<<endr
   <<-44*3.141593/180.0<<endr
   <<-90*3.141593/180.0<<endr
   <<-144*3.141593/180.0<<endr
   <<144*3.141593/180.0;
  A.fill(0);
  //A.print("A:");

r=pow(pow(robot.GetXPos(),2)+pow(robot.GetYPos(),2),1/2.0);

//  ofstream fp;
//  fp.open("datosRobot2.txt");
//a=robot.GetYaw();
//while(a<=3.141593/4)
//{
//	yisus.Read();
//	a=robot.GetYaw();
//	robot.SetSpeed(0.0,0.2);
//}
int i=0;

 while(i<400)
 {
   yisus.Read();
   x = robot.GetXPos();
   y = robot.GetYPos();
   a = robot.GetYaw();
   r=pow(pow(x,2)+pow(y,2),1/2.0);
   //sonares
   s0=sonares[0];
   s1=sonares[1];
   s2=sonares[2];
   s3=sonares[3];
   s4=sonares[4];
   s5=sonares[5];
   s6=sonares[6];
   s7=sonares[7];
  //velocidad
   robot.SetSpeed(0.25,0.0);
 

   A(i,0)=s0*cos(a+(90*3.141593/180.0)-M_PI/2.0)+x+3;
   A(i,1)=s0*sin(a+(90*3.141593/180.0)-M_PI/2.0)+y+2;
   A(i,2)=s1*cos(a+(44*3.141593/180.0)-M_PI/2.0)+x+3;
   A(i,3)=s1*sin(a+(44*3.141593/180.0)-M_PI/2.0)+y+2;
   A(i,4)=s2*cos(a+(12*3.141593/180.0)-M_PI/2.0)+x+3;
   A(i,5)=s2*sin(a+(12*3.141593/180.0)-M_PI/2.0)+y+2;
   A(i,6)=s3*cos(a+(-12*3.141593/180.0)-M_PI/2.0)+x+3;
   A(i,7)=s3*sin(a+(-12*3.141593/180.0)-M_PI/2.0)+y+2;
   A(i,8)=s4*cos(a+(-44*3.141593/180.0)-M_PI/2.0)+x+3;
   A(i,9)=s4*sin(a+(-44*3.141593/180.0)-M_PI/2.0)+y+2;
   A(i,10)=s5*cos(a+(-90*3.141593/180.0)-M_PI/2.0)+x+3;
   A(i,11)=s5*sin(a+(-90*3.141593/180.0)-M_PI/2.0)+y+2;
   A(i,12)=s6*cos(a+(-144*3.141593/180.0)-M_PI/2.0)+x+3;
   A(i,13)=s6*sin(a+(-144*3.141593/180.0)-M_PI/2.0)+y+2;
   A(i,14)=s7*cos(a+(144*3.141593/180.0)-M_PI/2.0)+x+3;
   A(i,15)=s7*sin(a+(144*3.141593/180.0)-M_PI/2.0)+y+2;

   A(i,16)=x+3;
   A(i,17)=y+2;

/*   int k=0;
   for(int j=1;j<=7;j+=2)
   {
		A(i,k)=sonares[j]*cos(a+B(j-1,0))+x;
		k++;
		A(i,k)=sonares[j]*sin(a+B(j-1,0))+y;
		k++;
   }
*/
   i++;
}

A.save("sonar.dat",raw_ascii);

   
/*   cout.precision(4);
   cerr << fixed << " (" << x << " , " << y << ")\tyaw: " << a<<" ";
   cerr<<s0<<" ";
   cerr<<s1<<" ";
   cerr<<s2<<" ";
   cerr<<s3<<" ";
   cerr<<s4<<" ";
   cerr<<s5<<" ";
   cerr<<s6<<" ";
   cerr<<s7<<" "<<endl;

   fp<<x<< " " <<y<< " " <<a<<" ";
   fp<<s0<<" ";
   fp<<s1<<" ";
   fp<<s2<<" ";
   fp<<s3<<" ";
   fp<<s4<<" ";
   fp<<s5<<" ";
//   fp<<s6<<" ";
   fp<<s7<<" "<<endl; */
 //  cout << fixed << "\tSonar : " << a << endl;
//fp.close();
return 0;
}
