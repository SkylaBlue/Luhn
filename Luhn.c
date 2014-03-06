// Luhn.c
// Luhn (aka mod 10) algorithm
#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include <stdbool.h>
#include <Windows.h>

#define btoa(x) x ? "True" : "False"

// Return length of a 64 bit integer
int calc_len(unsigned __int64 input)
{
	return log10(floor(input))+1;
}

// Calculate input to the nth power
unsigned __int64 calc_power(unsigned __int64 input, int n)
{
	unsigned __int64 temp = 1;

	while (n--)
	{
		temp *= input;
	}
	return temp;
} 

// Return the nth digit of a 64 bit integer
int nthdigit(unsigned __int64 x, int n)
{
	unsigned __int64 power = calc_power(10, n);
	return (x/power) % 10;
}

// Reverse a 64 bit integer
unsigned __int64 flip(unsigned __int64 num)
{
	unsigned __int64 final = 0;
	while (num > 0)
	{
		result = (result * 10) + (num % 10);
		num = num / 10;
	}
	return result;
}

// Self explanitory
void calc_odds(unsigned __int64 input, int *odd_array)
{
	int counter = 0;
	int len = calc_len(input)-3;
	
	while (len >= 0)
	{
		int single = nthdigit(flip(input), len);
		odd_array[counter] = single;
		counter++;
		len -= 2;
	}
}

// Self explanitory
void calc_evens(unsigned __int64 input, int *even_array)
{
	int counter = 0;
	int len = calc_len(input)-2;
	
	while (len > 0)
	{
		int doubled = nthdigit(flip(input), len) * 2;
		if (doubled > 9)
		{
			int combine = nthdigit(flip(doubled), 0) + nthdigit(flip(doubled), 1);
			even_array[counter] = combine;
			counter++;
		}
		
		else
		{
			even_array[counter] = doubled;
			counter++;
		}
		len -= 2;
	}
}

bool isValid(int s, int check)
{
	if ((s+check) % 10 == 0)
	{
		return true;
	}
	
	else
	{
		return false;
	}
}

int main()
{
	unsigned __int64 test = 342781835011463; //7992739871 as another test
	int check_digit = nthdigit(flip(test), calc_len(test)-1);
	
	int array_size = calc_len(test) / 2;
	int odds[array_size+1];
	int evens[array_size+1];
	
	calc_evens(test, evens);
	calc_odds(test, odds);
	
	int i, sum = 0;
	for (i = 0; i < array_size; ++i)
	{
		sum += (odds[i] + evens[i]);
	}
	
	/*
	Uncomment this to calculate the check digit
	sum = sum * 9;
	int check = nthdigit(flip(sum), calc_len(sum)-1);
	printf("CHECK=%i\n", check);
	*/
	printf("VALID=%s", btoa(isValid(sum, check_digit)));
	
	return 0;
}
