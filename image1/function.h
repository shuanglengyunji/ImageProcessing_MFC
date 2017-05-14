
#include "stdafx.h"

void BMP_To_Matrix(BITMAPINFO* pBmpInfo,BYTE* pBmpData,unsigned char **** c);
void Matrix_To_BMP(BITMAPINFO* pBmpInfo,BYTE* pBmpData,unsigned char *** c);

void Fix1(unsigned char *** c,int height,int width);
void Fix2(unsigned char *** c,int height,int width);
