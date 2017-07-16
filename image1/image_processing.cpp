#include "stdafx.h"
#include <math.h>

#include "image_processing.h"

#define boolean_T bool

unsigned char gray_array[IMG_WIDTH*IMG_HEIGHT] = { 0 };
unsigned char gray_across_array[IMG_WIDTH*IMG_HEIGHT] = { 0 };
unsigned char result_across_array[IMG_WIDTH*IMG_HEIGHT] = { 0 };
unsigned char result_array[IMG_WIDTH*IMG_HEIGHT] = { 0 };
float length = 0;
float speed = 0;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//图像处理函数
void Image_Fix(void)	//图像算法
{
	//demo
	length = 123.456;
	speed = -44.2233;
	for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	{
		result_across_array[i] = gray_across_array[i];
	}

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void across()	//把图翻到对角的位置，生成gray_across_array
{
	for (int i = 0; i < 48; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			gray_across_array[j * 48 + i] = gray_array[i * 80 + j];
		}
	}
}

void back_across()	//把图翻到对角的位置，生成gray_across_array
{
	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < 48; j++)
		{
			result_array[j * 80 + i] = result_across_array[i * 48 + j];
		}
	}
}

void processing(unsigned char * c, double * pd1, double * pd2)
{
	//拷贝图像
	for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	{
		gray_array[i] = c[i];
	}

	across();	//生成对角线图像

	Image_Fix();

	back_across();	//恢复正常非对角线图像

	//反向拷贝
	*pd1 = length;
	*pd2 = speed;
	for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	{
		c[i] = result_array[i];
	}
}