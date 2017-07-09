#include "stdafx.h"

#define IMG_WIDTH	80
#define IMG_HEIGHT	48

extern unsigned char gray_array[IMG_WIDTH*IMG_HEIGHT];
extern float length;
extern float speed;

void processing(unsigned char * c,double * pd1,double * pd2);