//Chris Park

#include "convert.h"

void toBinary(int decimal, char * bin)
{
	int i;
	char binary[MAX_BITS];
	
	i = 0;
	while(decimal > 0)
	{
		binary[i] = decimal % 2;
		i++;
		decimal /= 2;
	}
	
	for(; i < MAX_BITS; i ++)
		binary[i] = 0;
	
	for(i = 0; i < MAX_BITS; i ++)
		bin[(MAX_BITS -1) - i] = binary[i];	
}

int getBits(int decimal)
{
	int i;
	
	for(i = 0; decimal != 1; i++)
		decimal /= 2;
	
	return i;
}

int toDecimal(char * binary, int bits)
{
	int i;
	int decimal = 0;
	
	for(i = 0; i < bits; i++)
		if(binary[i] == 1)
		{
			decimal = (1 * power(2, (bits - 1) - i)) + decimal;
		}
	return decimal;
}

int power(int base, int exp)
{
	int i;
	int pow = 1;
	
	for( i = 1; i <= exp; i++)
		pow = pow * base;
	
	return pow;
}

