#include<stdio.h>
void printf_prime(int n);
void printf_prime_factors(int n);
int main(void)
{
	printf_prime(50);
	printf_prime_factors(10000);
	return 0;
}
int is_prime(int n)
{
	for (int i = 2; i < n; ++i)
		if (n%i == 0)
			return 0;
		 return 1;

}
void printf_prime(int n)
{
	for (int i = 2; i < n; ++i)
		if (is_prime(i) == 1)
			printf("%i\n", i);
}
void printf_factors(int n,int i)

{
	
	while (n%i == 0)
	{
		printf("%i\t", i); n /= i;
	}
}
	void printf_prime_factors(int n)
{
		int i = 2;
    do {
		if (is_prime(i))
		  {
			printf_factors(n, i);

		   }
		++i;
		} while (n > 1);

}