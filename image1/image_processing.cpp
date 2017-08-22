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
//=========================================ͼ���������ڴ��к���=============================================
//==============================================================================================================

//���ô˺궨������������������
#define __ACROSS_IMAGE


//ͼ������
void Image_Fix(void)	//ͼ���㷨
{
	////demo1 -- �ж�ȡģʽ
	////��ģʽ����__ACROSS_IMAGE�궨��
	//length = 123.456;
	//speed = -44.2233;
	//for (int i = 0; i < IMG_SIZE; i++)
	//{
	//	result_across_array[i] = gray_across_array[i];
	//}

	//demo2 -- ������ģʽ
	//��ģʽ����__ACROSS_IMAGE�궨��

	double tmp_array[IMG_SIZE] = { 0 };	//��ʱ��������

	length = 123.456;
	speed = -44.2233;
	
	//����������tmp_array�п�������
	for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	{
		result_across_array[i] = (unsigned char)(tmp_array[i]);
	}


	////demo3 -- ������ģʽ���±�ģʽ��
	////��ģʽ����__ACROSS_IMAGE�궨��
	//length = 123.456;
	//speed = -44.2233;

	//double tmp_array[IMG_SIZE] = { 0 };
	//
	////���дһ��ͼ��任��Ϊͼ��������
	//for (int i = 0; i < IMG_SIZE; i++)
	//{
	//	tmp_array[i] = (double)gray_across_array[i] * 2;
	//}

	////ȡ����
	//for (int i = 0; i < IMG_SIZE; i++)
	//{
	//	tmp_array[i] = log(tmp_array[i]) / log(2.0);	//ȡ2�Ķ���
	//}

	////Ѱ�����ֵ
	//double max_t = 1;
	//for (int i = 0; i < IMG_SIZE; i++)
	//{
	//	if (tmp_array[i] > max_t)
	//		max_t = tmp_array[i];
	//}

	////�������ű���
	//double mult = 1;	//����
	//mult = 255.0 / max_t;

	////����������tmp_array�п�������
	//for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	//{
	//	result_across_array[i] = (unsigned char)(tmp_array[i] * mult);
	//}

}

//==============================================================================================================
//=========================================ͼ������ʵ�������ֹ=============================================
//==============================================================================================================

void across()	//��ͼ�����Խǵ�λ�ã�����gray_across_array
{
	for (int i = 0; i < 48; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			gray_across_array[j * 48 + i] = gray_array[i * 80 + j];
		}
	}
}

void back_across()	//��ͼ�����Խǵ�λ�ã�����gray_across_array
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
	//����ͼ��
	for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	{
		gray_array[i] = c[i];
	}

#ifdef __ACROSS_IMAGE

	across();	//���ɶԽ���ͼ��

#endif

	Image_Fix();

#ifdef __ACROSS_IMAGE

	back_across();	//�ָ������ǶԽ���ͼ��

#endif

	//���򿽱�
	*pd1 = length;
	*pd2 = speed;
	for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	{
		c[i] = result_array[i];
	}
}