// Gen.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <stdint.h>
#include <iostream>
#include <string>


int main()
{

	/*
	I0				I1				I2				I3
	00 - 03				07				11				15
	01 - 02 03			06 07			10 11			14 15
	10 - 01 02 03		05 06 07 		09 10 11 		13 14 15
	11 - 00 01 02 03	04 05 06 07		08 09 10 11		12 13 14 15

	Mask = I3 I2 I1 I0

	*/

	uint8_t buf[16];
	uint8_t pos = 0;
	uint8_t t;

	uint8_t lengths[256];
	for (uint16_t i = 0; i < 256; ++i) {
		memset(buf, 0x80, 16);
		pos = 0;

		//I0
		t = (i & 0b00000011) + 1;
		for (uint8_t j = 0; j < t; ++j) {
			buf[pos++] = j;
		}
		//I1
		t = ((i >> 2) & 0b00000011) + 1;
		for (uint8_t j = 4; j < 4 + t; ++j) {
			buf[pos++] = j;
		}
		//I2
		t = ((i >> 4) & 0b00000011) + 1;
		for (uint8_t j = 8; j < 8+t; ++j) {
			buf[pos++] = j;
		}

		//I3
		t = ((i >> 6) & 0b00000011) + 1;
		for (uint8_t j = 12; j < 12+t; ++j) {
			buf[pos++] = j;
		}

		lengths[i] = pos;
		
		std::cout << "{";
		std::string sep = "";
		for (uint8_t j = 0; j < 16; ++j) {
			std::cout << sep << (uint32_t)(buf[j]) ;
			sep = ", ";
		}
		std::cout << "}," << std::endl;
		 
	}


	for (uint16_t i = 0; i < 256; ++i) {
		std::cout << (uint32_t)lengths[i] << ", ";
		if (i % 16 == 0) {
			std::cout << std::endl;
		}
		
	}

    return 0;
}

