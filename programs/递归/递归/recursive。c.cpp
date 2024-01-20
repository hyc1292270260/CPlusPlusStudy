#include<stdio.h>
int sum(int n);
int factorial(int n);
void hanoi(int n, char from, char via, char to);
int gcd(int a, int b);
int icm(int a, int b);
int main(void)
{
	int result1 = sum(10);
	printf("%i\n", result1);
	int result2 = factorial(10);
	printf("%i\n", result2);
	hanoi(3, 'A', 'B', 'C');
	int result3=gcd(695, 1112);
	printf("%i\n", result3);
	int result4=icm(36, 48);
	printf("%i\n", result4);
	return 0;
}
int sum(int n)
{
	if (n == 1)
		return 1;
	else
		return n + sum(n - 1);
}
int factorial(int n)
{
	if (n == 1)
		return 1;
	else 
		return n * factorial(n - 1);
	
}
void hanoi(int n, char from, char via, char to)
{
	if (n ==1)
		printf("%c->%c\n", from, to);
	else {
		hanoi(n - 1, from, to, via);
		printf("%c->%c\n", from, to);
		hanoi(n - 1, via, from, to);
	     }

}
int gcd(int a, int b)                   //最大公约数
{
	if ((a = a%b )== 0)
		return b;
	else 
		return  gcd(b, a);

}
int icm(int a, int b)                    //最小公倍数
{
	return(a*b/ (gcd(b, a)));

}