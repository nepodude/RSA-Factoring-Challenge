#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * print_uint128 - Prints an unsigned __int128 number
 * @n: The number to print
 */
void print_uint128(unsigned __int128 n)
{
	if (n == 0)
	{
		printf("0");
		return;
	}

	char buffer[40];
	int i = 0;

	while (n > 0)
	{
		buffer[i++] = (n % 10) + '0';
		n /= 10;
	}

	while (i > 0)
	{
		putchar(buffer[--i]);
	}
}

/**
 * string_to_uint128 - Converts a string to an unsigned __int128
 * @str: The string to convert
 * Return: The converted unsigned __int128 value
 */
unsigned __int128 string_to_uint128(const char *str)
{
	unsigned __int128 result = 0;

	while (*str)
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

/**
* factorize - factorizes integer n
* @n: integer to be factorized
*/
void factorize(unsigned __int128 n)
{
	unsigned __int128 p, q;

	if (n % 2 == 0)
	{
		q = n / 2;
		print_uint128(n);
		printf("=%llu*%llu\n", (unsigned long long)q, (unsigned long long)2);
		return;
	}

	for (p = 3; p * p <= n; p += 2)
	{
		if (n % p == 0)
		{
			q = n / p;
			print_uint128(n);
			printf("=");
			print_uint128(q);
			printf("*");
			print_uint128(p);
			printf("\n");
			return;
		}
	}
	/* If no factors found, the number is prime */
	print_uint128(n);
	printf("=");
	print_uint128(n);
	printf("*1\n");
}

/**
* main - main function
* @argc: argument count
* @argv: a vector whose commandline arguments as elements.
* Return: returns 0 on success and 1 on any failure
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		return (1);
	}

	FILE *file = fopen(argv[1], "r");

	if (!file)
	{
		perror("Error opening file");
		return (1);
	}

	char buffer[40];

	while (fgets(buffer, sizeof(buffer), file))
	{
		buffer[strcspn(buffer, "\n")] = 0;
		unsigned __int128 n = string_to_uint128(buffer);

		factorize(n);
	}

	fclose(file);
	return (0);
}
