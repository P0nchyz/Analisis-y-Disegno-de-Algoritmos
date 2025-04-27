#include "binary.h"

#include <stdio.h>

uint8_t push_bin(uint8_t num, int bin)
{
	num = num << 1;
	num += bin;
	return num;
}

int get_bit(uint8_t num, int pos)
{
	uint8_t mask = 1 << pos;
	return num & mask;
}


void print_uint8_b(uint8_t value) {
	for (int i = 7; i >= 0; i--) {
		printf("%c", (value & (1 << i)) ? '1' : '0');
	}
	printf(" ");
}