#ifndef CONVERT_H
#define CONVERT_H

#include <stdlib.h>
#include <stdio.h>
#define MAX_BITS 32

void toBinary(int decimal, char * bin);
int toDecimal(char * binary, int bits);
int getBits(int decimal);
int power(int base, int exp);


#endif //CONVERT_H
