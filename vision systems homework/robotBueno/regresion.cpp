#include<armadillo>
#include<cmath>
#include<iostream>

using namespace std;
using namespace arma;


int N=7; //7


int main()
{
	int i,j,k;
	mat D,A(N,N),x(N,1),y(N,1), y1(N,1),x1(N,1),y2(N,1),x2(N,1),y3(N,1),x3(N,1);
	A.fill(0);
	D.load("datos2.txt",raw_ascii);
	float temp=0.0;

	A(0,0)=D.n_rows;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			for(k=0;k<D.n_rows;k++)
			{
				if(j!=0||i!=0)
					//A(i,j)+=pow(D(k,2),i+j);
					A(i,j)+=pow(D(k,3),i+j);
				if(i==0)
				{
					//y(j,0)+=pow(D(k,2),j)*D(k,0);
					y(j,0)+=pow(D(k,3),j)*D(k,0);		//x derivada
					//y1(j,0)+=pow(D(k,2),j)*D(k,1);
					y1(j,0)+=pow(D(k,3),j)*D(k,1);   ///D(k,1)   //y derivada
				}
			}
		}
	}
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			for(k=0;k<D.n_rows;k++)
			{
				if(j!=0||i!=0)
					//A(i,j)+=pow(D(k,2),i+j);
					A(i,j)+=pow(D(k,3),i+j);
				if(i==0)
				{
					//y(j,0)+=pow(D(k,2),j)*D(k,0);
					y2(j,0)+=pow(D(k,3),j)*sqrt(pow(D(k,0),2)+pow(D(k,1),2));		//s derivada
					//y1(j,0)+=pow(D(k,2),j)*D(k,1);
					if(j==0)
					y3(j,0)=0;
					else
					y3(j,0)+=pow(D(k,3),j)*atan(D(k,1)/D(k,0))-y3(j-1,0);   ///D(k,1)   //y derivada
				}
			}
		}
	}



	temp=sum(A.col(2));
	cout<<sum(A,0)<<endl;
	A.print("A: ");
	cout<<"A-1: \n"<<inv(A)<<endl;
	y.print("y: ");
	
	x=inv(A)*y;
	x1=inv(A)*y1;
	x2=inv(A)*y2;
	x3=inv(A)*y3;
	//x=A*y;
	x.print("x: ");
	x1.print("x1: ");
	for(i=0;i<N; i++)
	{
		if(i==0)
			cout<<"s(x)="<<x(i,0)<<"*x**"<<i;
		else	
			cout<<"+"<<x(i,0)<<"*x**"<<i;
	}
		cout<<endl;
	for(i=0;i<N; i++)
	{
		if(i==0)
			cout<<"t(x)="<<x1(i,0)<<"*x**"<<i;			
		else		
			cout<<"+"<<x1(i,0)<<"*x**"<<i;
	}
		cout<<endl;
	for(i=0;i<N; i++)
	{
		if(i==0)
			cout<<"v(x)="<<x(i,0)*i<<"*x**"<<i-1;	
		else
			cout<<"+"<<x(i,0)*i<<"*x**"<<i-1;
	}
		cout<<endl;
	for(i=0;i<N; i++)
	{
		if(i==0)
			cout<<"w(x)="<<x1(i,0)<<"*x**"<<i;			
		else
			cout<<"+"<<x1(i,0)*i<<"*x**"<<i-1;
	}
		cout<<endl<<endl<<endl;

//////////////////////////
	for(i=0;i<N; i++)
	{
		if(i==0)
			cout<<"v="<<x(i,0)<<"*pow(t,"<<i<<")";
		else	
			cout<<"+"<<x(i,0)<<"*pow(t,"<<i<<")";
	}
		cout<<";"<<endl;

	for(i=0;i<N; i++)
	{
		if(i==0)
			cout<<"w="<<x1(i,0)<<"*pow(t,"<<i<<")";			
		else		
			cout<<"+"<<x1(i,0)<<"*pow(t,"<<i<<")";
	}
		cout<<";"<<endl;

	for(i=0;i<N; i++)
	{
		if(i==0)
			cout<<"v="<<x(i,0)*i<<"*pow(t,"<<i-1<<")";	
		else
			cout<<"+"<<x(i,0)*i<<"*pow(t,"<<i-1<<")";
	}
		cout<<";"<<endl;
	for(i=0;i<N; i++)
	{
		if(i==0)
			cout<<"w="<<x1(i,0)<<"*pow(t,"<<i-1<<")";			
		else
			cout<<"+"<<x1(i,0)*i<<"*pow(t,"<<i-1<<")";
	}
		cout<<";"<<endl<<endl<<endl;
///////////////////
	for(i=0;i<N; i++)
	{
		if(i==0)
			cout<<"v(x)="<<x2(i,0)*i<<"*x**"<<i-1;	
		else
			cout<<"+"<<x2(i,0)*i<<"*x**"<<i-1;
	}
		cout<<endl;
	for(i=0;i<N; i++)
	{
		if(i==0)
			cout<<"w(x)="<<x3(i,0)<<"*x**"<<i;			
		else
			cout<<"+"<<x3(i,0)*i<<"*x**"<<i-1;
	}
		cout<<endl<<endl<<endl;
	return 0;
}
