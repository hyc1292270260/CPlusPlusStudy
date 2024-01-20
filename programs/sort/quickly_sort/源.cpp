#include<stdio.h>
//time complexity O(nlog2^n)
//space complexity O(nlog2^n)
//unstable
void exchange(int a[], int i, int j)
{
	a[i] = a[i] ^ a[j];
	a[j] = a[i] ^ a[j];
	a[i] = a[i] ^ a[j];
	return;

}

void quick_sort(int a[], int left, int right)
{
	int p = left, min = left + 1, max = right;
	if (left >= right)          //�ݹ���ֹ����
	{
		return;
	}
	while (min < max)
	{
		while (min < max && a[max] >= a[p])  //�Ҳ࿪ʼ�Ƚ�
			max--;
		while (min < max && a[min] < a[p]) //��࿪ʼ�Ƚ�
			min++;
		if (min < max)                      //����
		{
			exchange(a, max, min);
		}
	}										//�ҵ�λ�ã�����
	if (a[p] > a[min])						//min û�б��жϣ�maxһֱ--
		exchange(a, p, min);
	else
	{
		min = p; max = p;
	}

	quick_sort(a, left, min - 1);//�ݹ����
	quick_sort(a, max + 1, right);//�ݹ��Ҳ�
}
int main(void)
{
	int i;
	int a[] = { 4,2,1,6,9,8,6,7,4,3 };
	int b[sizeof a / sizeof a[0]];
	quick_sort(a, 0, sizeof a / sizeof a[0] - 1);
	for (i = 0; i < (sizeof a / sizeof a[0]); i++)
		printf("%3i", a[i]);
	return 0;
}