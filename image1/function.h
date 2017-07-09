
#include "stdafx.h"

void BMP_To_Matrix(BITMAPINFO* pBmpInfo,BYTE* pBmpData,unsigned char **** c);
void Matrix_To_BMP(BITMAPINFO* pBmpInfo,BYTE* pBmpData,unsigned char *** c);

void BMP_To_GrayMatrix(BITMAPINFO* pBmpInfo, BYTE* pBmpData, unsigned char ** c);
void GrayMatrix_To_BMP(BITMAPINFO* pBmpInfo, BYTE* pBmpData, unsigned char ** c);

void Fix1(unsigned char * c,double * pd1,double * pd2);
