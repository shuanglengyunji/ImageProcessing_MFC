#include "stdafx.h"

#include "image_processing.h"

unsigned char gray_array[IMG_WIDTH*IMG_HEIGHT] = { 0 };
unsigned char result_array[IMG_WIDTH*IMG_HEIGHT] = { 0 };
float length = 0;
float speed = 0;

//Í¼Ïñ´¦Àíº¯Êý
void Image_Fix(void)	//Í¼ÏñËã·¨
{
	//demo
	length = 123.456;
	speed = -44.2233;
	for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	{
		result_array[i] = gray_array[i] - 0x80;
	}
}

void processing(unsigned char * c, double * pd1, double * pd2)
{
	//¿½±´Í¼Ïñ
	for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	{
		gray_array[i] = c[i];
	}

	Image_Fix();

	//·´Ïò¿½±´
	*pd1 = length;
	*pd2 = speed;
	for (int i = 0; i < IMG_WIDTH*IMG_HEIGHT; i++)
	{
		c[i] = result_array[i];
	}
}