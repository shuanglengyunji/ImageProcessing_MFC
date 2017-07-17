#include "stdafx.h"

#define IMG_WIDTH	80
#define IMG_HEIGHT	48
#define IMG_SIZE	(IMG_WIDTH * IMG_HEIGHT)

#define boolean_T bool

extern unsigned char gray_array[IMG_SIZE];
extern float length;
extern float speed;

void processing(unsigned char * c,double * pd1,double * pd2);