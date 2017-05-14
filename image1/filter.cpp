#include "stdafx.h"
#include "math.h"
#include "filter.h"

extern int stopflag_1;
extern int stopflag_2;

void Forward_Fourier(unsigned char *** c,int w,int h,
						double *** r,double *** i)
{
	double R,I,uw,vh,cd;
	double wh=w*h;
	for(int v=0;v<h;v++)
	{
		for(int u=0;u<w;u++)
		{
			uw = (float)u/w;
			vh = (float)v/h;
			for(int k=0;k<3;k++)
			{
				R=0;
				I=0;
				for(int y=0;y<h;y++)
				{
					for(int x=0;x<w;x++)
					{
						cd = 6.28*(uw*x+vh*y);
						R=R+c[y][x][k]*cos(cd);
						I=I-c[y][x][k]*sin(cd);
					}
				}
			r[v][u][k] = R/wh;
			i[v][u][k] = I/wh;
			}
		}
	}
}

void Backward_Fourier(double *** r,double *** i,
						int h,int w,unsigned char *** c)
{
	double R,I,E,xw,yh,cd;
	for(int y=0;y<h;y++)
	{
		for(int x=0;x<w;x++)
		{
			xw = (float)x/w;
			yh = (float)y/h;
			for(int k=0;k<3;k++)
			{
				R = 0;
				I = 0;
				for(int v=0;v<h;v++)
				{
					for(int u=0;u<w;u++)
					{
						cd = 6.28*(xw*u+yh*v);
						R=R+r[v][u][k]*cos(cd);
						I=I-i[v][u][k]*sin(cd);
					}
				}
				E=R+I;
				if(E>255)		E=255;
				else if(E<0)	E=0;
				c[y][x][k]=E;
			}
		}
	}
}
