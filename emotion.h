#ifndef DEF_EMOTION
#define DEF_EMOTION


struct emotion
{
	unsigned char tonicity = 127;
	unsigned char destination = 127;
	unsigned char value = 127;

	unsigned char const MAX = 255;
};

#endif