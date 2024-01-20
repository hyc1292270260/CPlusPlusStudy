#include<stdio.h>
int write_file(const char *name);
int read_file(const char *name);
int main(void)
{

	//write_file("e:/aa.txt");
	read_file("e:/aa.txt");
	
	return 0;  
}
int write_file(const char *name)
{
	int i = 201;
	int result = 0;
	FILE* file = fopen("e:/aa.txt", "w");//原有文字w覆盖，a追加
	if (file == NULL)
		return 0;
	result = fwrite(&i, sizeof(i), 1, file);
	fclose(file);
	file = NULL;
	return result;
}
int read_file(const char *name) 
{
	int i=0 ; int result = 0;
	FILE* file = fopen("e:/aa.txt", "r");
	if (!file)
		return 0;
	result = fread(&i, sizeof(i), 1, file);
	fclose(file);
	printf("%i\n",i);
	return result;

}