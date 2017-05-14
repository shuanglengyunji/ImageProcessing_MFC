#include "stdafx.h"

void Forward_Fourier(unsigned char *** c,int w,int h,double *** r,double *** i);
void Backward_Fourier(double *** r,double *** i,int h,int w,unsigned char *** c);