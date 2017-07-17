#include "stdafx.h"
#include <math.h>

#include "image_processing.h"

unsigned char gray_array[IMG_SIZE] = { 0 };
unsigned char gray_across_array[IMG_SIZE] = { 0 };
unsigned char result_across_array[IMG_SIZE] = { 0 };
unsigned char result_array[IMG_SIZE] = { 0 };
float length = 0;
float speed = 0;

//==============================================================================================================
//=========================================图像处理函数放在此行后面=============================================
//==============================================================================================================

//启用此宏定义则启用列向量数据
#define __ACROSS_IMAGE					


//图像处理函数
void Image_Fix(void)	//图像算法
{
	////demo1 -- 行读取模式
	////此模式禁用__ACROSS_IMAGE宏定义
	//length = 123.456;
	//speed = -44.2233;
	//for (int i = 0; i < IMG_SIZE; i++)
	//{
	//	result_across_array[i] = gray_across_array[i];
	//}

	//demo2 -- 列向量模式
	//此模式启用__ACROSS_IMAGE宏定义

	double tmp_array[IMG_SIZE] = { 0 };	//临时变量数组

	length = 123.456;
	speed = -44.2233;
	
	//将运算结果从tmp_array中拷贝出来
	for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	{
		result_across_array[i] = (unsigned char)(tmp_array[i]);
	}


	////demo3 -- 列向量模式（懵逼模式）
	////此模式启用__ACROSS_IMAGE宏定义
	//length = 123.456;
	//speed = -44.2233;

	//double tmp_array[IMG_SIZE] = { 0 };
	//
	////随便写一个图像变换作为图像处理例子
	//for (int i = 0; i < IMG_SIZE; i++)
	//{
	//	tmp_array[i] = (double)gray_across_array[i] * 2;
	//}

	////取对数
	//for (int i = 0; i < IMG_SIZE; i++)
	//{
	//	tmp_array[i] = log(tmp_array[i]) / log(2.0);	//取2的对数
	//}

	////寻找最大值
	//double max_t = 1;
	//for (int i = 0; i < IMG_SIZE; i++)
	//{
	//	if (tmp_array[i] > max_t)
	//		max_t = tmp_array[i];
	//}

	////计算缩放倍速
	//double mult = 1;	//倍率
	//mult = 255.0 / max_t;

	////将运算结果从tmp_array中拷贝出来
	//for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	//{
	//	result_across_array[i] = (unsigned char)(tmp_array[i] * mult);
	//}

}

//==============================================================================================================
//=========================================图像处理函数实现区域截止=============================================
//==============================================================================================================

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

#ifdef __ACROSS_IMAGE

	across();	//生成对角线图像

#endif

	Image_Fix();

#ifdef __ACROSS_IMAGE

	back_across();	//恢复正常非对角线图像

#endif

	//反向拷贝
	*pd1 = length;
	*pd2 = speed;
	for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	{
		c[i] = result_array[i];
	}
}