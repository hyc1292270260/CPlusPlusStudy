#include<stdio.h>
#include<string.h>
int str_len(char a[]);
void str_cpy(char to[], char from[]);
void str_cat(char to[], char from[]);
int str_cmp(char a[], char b[]);
int str_str(char a[], char b[]);
int main(void)
{
	char a[10] = "Hello";
	char b[8] = "hi";
	int l = str_cmp(a, b);
	int pos = str_str(a, "el");

	/*str_cat(a, b);
	printf("%s", a);*/
	//int length = str_len(a);str_cpy(b, a);
	//strcpy(b, a);


	return 0;

}
int str_len(char a[])
{
	int i = -1;
	while (a[++i]);
	return i;
}
void str_cpy(char to[], char from[])
{
	int i = 0;
	while (to[i] = from[i++]);
	return;
}
void str_cat(char to[], char from[])
{
	int i = 0, j = 0;
	while (to[i])
		++i;

	for (; from[j] != 0; ++i, ++j)
		to[i] = from[j];
	to[i] = 0;
	return;

}
int str_cmp(char a[], char b[])
{
	int i = 0;
	while (a[i] == b[i] && a[i] != 0)   
	{
		i++;

	}
	if (a[i] > b[i])
		return 1;
	else if (a[i] < b[i])
		return -1;
	return 0;

}
int str_str(const char a[], const char b[])

{
	int i = 0, j = 0;
	while (a[i])
	{
		j = 0; while (a[i + j] == b[j] && b[j] != 0)
		{
			++j;
			if (!b[j])
				return i;
		}

		++i;
	}

	return -1;

}
