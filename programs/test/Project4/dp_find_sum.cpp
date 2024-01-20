#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
int rec_solve_dp(int* p, int i, int sum)
{
	//rec
	if (sum == 0)
		return 1;								//found
	else if(i==0)
	{
		return p[i] == sum ? 1 : 0;				//the last
	}
	else if (p[i]>sum)
	{
		return rec_solve_dp(p, i - 1, sum);			//>
	}
	else
	{
		return rec_solve_dp(p, i - 1, sum) || rec_solve_dp(p, i - 1, sum - p[i]);  
	}
}
/*int solve_dp(int* p, int n, int sum)
{
	int i, j;
	int**opt = (int**)malloc(n* sizeof(int));//�������ָ�루������
	for (i = 0; i < n; i++);//ÿ�ж��ж�����
		opt[i] =(int*) malloc((sum + 1) * sizeof(int *));//ע���ά����Ķ�̬���ٷ���
	for (i = 0; i <= sum; i++)
		opt[0][i] = 0;//��һ�У���Ӧ�ݹ��nΪ0ʱ�������
	for (i = 0; i < n; i++)
		opt[i][0] = 1;//��keyΪ0ʱ�����ж�Ϊ1
	opt[0][p[0]] = 1;//�����p[0]==key�����ֵΪ1�����ǵ�ԭ����0��
	for (i = 1; i < n; i++)//����p���飬�Լ���ά�������
		for (j = 1; j <= sum; j++)//��ά�������
		{
			if (p[i] > j)
				opt[i][j] = opt[i - 1][j];
			else
				opt[i][j] = opt[i - 1][j - p[i]] || opt[i - 1][j];
		}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j <= sum; j++)
			printf("%d ", opt[i][j]);
		putchar('\n');
	}//��ӡ��ά���飨������֤��
	j = opt[n - 1][sum];//������
	free(opt);//��ʱ�ͷŵ���ά����
	return j;

}*/
int main(void)
{
	
	int n, i, key;
	
	std::cin >> n;
	int *p =(int*) malloc(n * sizeof(int));
	printf("Input the array\n");
	for (i = 0; i < n; i++)
		scanf("%d", &p[i]);
	/*int arr[6] = { 3, 34, 4, 12, 5, 2 };
	p = arr;*/
	int len = n/*sizeof(arr)/sizeof(int)*/;
	
		if (rec_solve_dp(p, len - 1, 9))
			printf("True\n");
		else
			printf("False\n");

		/*if (solve_dp(arr, len - 1, 11))
			printf("True\n");
		else
			printf("False\n");*/

	return 0;
	
}