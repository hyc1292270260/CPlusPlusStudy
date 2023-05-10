#include "RingBuffer.h"
#include <random>
#include <math.h>
#include <iostream>
int main()
{
	int initSize = 8;
	const char* data = "012345678901234567890123456789012345678901234567890123456789";
	RingBuffer buffer = RingBuffer(initSize);
	buffer.write(data);
	buffer.printAll();
	char out[108];
	buffer.read(out, 20);
	buffer.printAll();
	buffer.write("aaaaaa");
	buffer.printAll();
	buffer.write("012345678901234567890123456789012345678901234567890123456789");
	buffer.printAll();
	buffer.read(out, 70);
	buffer.printAll();
	buffer.clear();
	buffer.printAll();
}
