
#include "stdafx.h"
#include "function.h"
#include "math.h"
#include "image_processing.h"

/*
* 24位真彩图图像数据存放：
* 每个像素占3字节，存放顺序BGR
* 从图像最后一行开始存，存到图像第一行
* 每一行中的顺序是从左到右
* 每一行像素所占字节数必须是4的整数倍，否则多余的像素不存颜色
*/

//创建像素点矩阵c
void BMP_To_Matrix(BITMAPINFO* pBmpInfo,BYTE* pBmpData,unsigned char **** c)
{	
	//开辟空间c
	*c = new unsigned char ** [pBmpInfo->bmiHeader.biHeight];	//申请c这个指针所对应的数组空间（一个biHeight长的数组）
	for(int i=0;i<pBmpInfo->bmiHeader.biHeight;i++)
	{
		(*c)[i] = new unsigned char * [pBmpInfo->bmiHeader.biWidth];	//每一行对应一个char *指针数组
		for(int j=0;j<pBmpInfo->bmiHeader.biWidth;j++)
		{
			(*c)[i][j] = new unsigned char [3];
		}
	}

	//计算每一行图像后面的无用字节数
	int offset = pBmpInfo->bmiHeader.biWidth * 3 % 4;	//判断是不是4的倍数，若不是，应将最后的多出来的像素舍弃
	if(offset == 0)offset = 4;

	//从原图拷贝到像素矩阵中
	for(int y=0; y<pBmpInfo->bmiHeader.biHeight ; y++)		//从最后一行开始拷贝，拷贝到第一行为止（BMP格式是从最后一行开始存储的）
	{
		for(int x=0; x<pBmpInfo->bmiHeader.biWidth ; x++)
		{
			char R,G,B;

			//从源数组读取像素点数据，写入到R G B三个变量中
			B = pBmpData[ y*(pBmpInfo->bmiHeader.biWidth*3+4-offset)+ 3*x ];
			G = pBmpData[ y*(pBmpInfo->bmiHeader.biWidth*3+4-offset) + 3*x + 1 ];
			R = pBmpData[ y*(pBmpInfo->bmiHeader.biWidth*3+4-offset) + 3*x + 2 ];
			
			//存入到定义的像素矩阵中
			(*c)[y][x][0] = B;
			(*c)[y][x][1] = G;
			(*c)[y][x][2] = R;
		}
	}
}

//删除像素点矩阵c
void Matrix_To_BMP(BITMAPINFO* pBmpInfo,BYTE* pBmpData,unsigned char *** c)
{
	//计算每一行图像后面的无用字节数
	int offset = pBmpInfo->bmiHeader.biWidth * 3 % 4;	//判断是不是4的倍数，若不是，应将最后的多出来的像素舍弃
	if(offset == 0)offset = 4;

	//从像素矩阵拷贝回原图
	for(int y=0; y<pBmpInfo->bmiHeader.biHeight ; y++)		//从最后一行开始拷贝，拷贝到第一行为止（BMP格式是从最后一行开始存储的）
	{
		for(int x=0; x<pBmpInfo->bmiHeader.biWidth ; x++)
		{
			char R,G,B;

			//从像素矩阵取像素点数据，写入到R G B三个变量中
			B = c[y][x][0];
			G = c[y][x][1];
			R = c[y][x][2];
			
			//存入到定义的像素矩阵中
			pBmpData[ y*(pBmpInfo->bmiHeader.biWidth*3+4-offset) + 3*x ]     = B;
			pBmpData[ y*(pBmpInfo->bmiHeader.biWidth*3+4-offset) + 3*x + 1 ] = G;
			pBmpData[ y*(pBmpInfo->bmiHeader.biWidth*3+4-offset) + 3*x + 2 ] = R;
		}
	}

	//删除空间c
	for (int i=0;i<pBmpInfo->bmiHeader.biHeight;i++)
	{
		for (int j=0;j<pBmpInfo->bmiHeader.biWidth;j++)
			delete[] c[i][j];
		delete[] c[i];
	}
	delete[] c;//new和delete是成对出现的，这里也要多重循环释放掉空间
	c = NULL;
}

//创建像素点矩阵c
void BMP_To_GrayMatrix(BITMAPINFO* pBmpInfo, BYTE* pBmpData, unsigned char ** c)
{
	//开辟一维数组空间
	(*c) = new unsigned char [pBmpInfo->bmiHeader.biHeight * pBmpInfo->bmiHeader.biWidth];

	//计算每一行图像后面的无用字节数
	int offset = pBmpInfo->bmiHeader.biWidth * 3 % 4;	//判断是不是4的倍数，若不是，应将最后的多出来的像素舍弃
	if (offset == 0)offset = 4;

	//从原图拷贝到像素矩阵中
	for (int y = 0; y<pBmpInfo->bmiHeader.biHeight; y++)		//从最后一行开始拷贝，拷贝到第一行为止（BMP格式是从最后一行开始存储的）
	{
		for (int x = 0; x<pBmpInfo->bmiHeader.biWidth; x++)
		{
			unsigned char R, G, B;
			unsigned char Gray;

			//从源数组读取像素点数据，写入到R G B三个变量中
			B = pBmpData[y*(pBmpInfo->bmiHeader.biWidth * 3 + 4 - offset) + 3 * x];
			G = pBmpData[y*(pBmpInfo->bmiHeader.biWidth * 3 + 4 - offset) + 3 * x + 1];
			R = pBmpData[y*(pBmpInfo->bmiHeader.biWidth * 3 + 4 - offset) + 3 * x + 2];

			Gray = (R * 299 + G * 587 + B * 114 + 500) / 1000;

			//存入到定义的像素矩阵中
			(*c)[y*pBmpInfo->bmiHeader.biWidth + x] = (unsigned char)Gray;
		}
	}
}

//删除像素点矩阵c
void GrayMatrix_To_BMP(BITMAPINFO* pBmpInfo, BYTE* pBmpData, unsigned char ** c)
{
	//计算每一行图像后面的无用字节数
	int offset = pBmpInfo->bmiHeader.biWidth * 3 % 4;	//判断是不是4的倍数，若不是，应将最后的多出来的像素舍弃
	if (offset == 0)offset = 4;

	//从像素矩阵拷贝回原图
	for (int y = 0; y<pBmpInfo->bmiHeader.biHeight; y++)		//从最后一行开始拷贝，拷贝到第一行为止（BMP格式是从最后一行开始存储的）
	{
		for (int x = 0; x<pBmpInfo->bmiHeader.biWidth; x++)
		{
			char R, G, B;

			//从像素矩阵取像素点数据，写入到R G B三个变量中
			B = (*c)[y*pBmpInfo->bmiHeader.biWidth + x];
			G = (*c)[y*pBmpInfo->bmiHeader.biWidth + x];
			R = (*c)[y*pBmpInfo->bmiHeader.biWidth + x];

			//存入到定义的像素矩阵中
			pBmpData[y*(pBmpInfo->bmiHeader.biWidth * 3 + 4 - offset) + 3 * x] = B;
			pBmpData[y*(pBmpInfo->bmiHeader.biWidth * 3 + 4 - offset) + 3 * x + 1] = G;
			pBmpData[y*(pBmpInfo->bmiHeader.biWidth * 3 + 4 - offset) + 3 * x + 2] = R;
		}
	}

	//删除空间c
	delete[] (*c);//new和delete是成对出现的，这里也要多重循环释放掉空间
	c = NULL;
}

void Fix1(unsigned char * c, double * pd1, double * pd2)
{
	processing(c, pd1, pd2);
}
