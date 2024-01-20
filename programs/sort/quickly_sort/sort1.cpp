#include<stdio.h>
#include <vector>
#include <time.h>
using namespace std;
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
	if (left >= right)          //递归终止条件
	{
		return;
	}
	while (min < max)
	{
		while (min < max && a[max] >= a[p])  //右侧开始比较
			max--;
		while (min < max && a[min] < a[p]) //左侧开始比较
			min++;
		if (min < max)                      //交换
		{
			exchange(a, max, min);
		}
	}										//找到位置，交换
	if (a[p] > a[min])						//min 没有被判断，max一直--
		exchange(a, p, min);
	else
	{
		min = p; max = p;
	}

	quick_sort(a, left, min - 1);//递归左侧
	quick_sort(a, max + 1, right);//递归右侧
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
void quick_sort1(int a[], int left, int right)
{
	if (left >= right)
		return;
	int p = a[left], min = left, max = right;
	while (min < max)
	{
		while (min < max && a[max] >= a[p])
			--max;
		a[min] = a[max];
		while (min < max && a[min] < a[p])
			++min;
		a[max] = a[min];
	}
	a[min] = p;
	quick_sort(a, left, min - 1);
	quick_sort(a, min + 1, right);
}
void bubble_sort1(int a[], int num)
{
	bool isExchange = false;
	for (int i = 0, isExchange = false; i < num - 1; ++i)
	{
		for (int j = 0; j < num - i - 1; ++j)
		{
			if (a[j] > a[j + 1])
				exchange(a, i, j);
			isExchange = true;
		}
		if (!isExchange)
			break;
	}
}
void select_sort1(int a[], int num)
{
	int min_index = 0;
	for (int i = 0; i < num - 1; ++i)
	{
		min_index = i;
		for (int j = i + 1; j < num; ++j)
		{
			if (a[j] < a[min_index])
			{
				min_index = j;
			}
		}
		if (min_index != i)
		{
			exchange(a, i, min_index);
		}
	}
}
void insert_sort1(int a[], int num)
{
	int temp, i , j;
	for (i = 1; i < num ; ++i)
	{
		temp = a[i];
		for (j = i - 1; j >= 0 && a[j] > temp; j --)
			a[j + 1] = a[j];
		a[j + 1] = temp;
	}
}
void shell_sort1(int a[], int num)
{
	for (int k = num/2 ; k >= 1; k/=2)
	{
		int temp, i, j;
		for (i = 1; i < num; ++i)
		{
			temp = a[i];
			for (j = i - k; j >= 0 && a[j] > temp; j-=k)
				a[j + k] = a[j];
			a[j + k] = temp;
		}
	}
	
}
void merge_sort1(int a[], int left, int right)
{
	if (left >= right)
		return;
	int mid = (right - left) / 2;
	merge_sort1(a, left, mid);
	merge_sort1(a, mid + 1, right);
	merge(a, left, mid, right);
}
int temp[10];
void merge(int a[], int left, int mid, int right)
{
	int p = 0, p1 = left, p2 = mid + 1;
	while (p1 <= mid && p2 <= right)
	{
		if (a[p1] < a[p2])
		{
			temp[p++] = a[p1++];
		}
		else
		{
			temp[p++] = a[p2++];
		}
	}
	while (p1 <= mid) 
	{
		temp[p++] = a[p1++];
	}
	while (p2 <= right)
	{
		temp[p++] = a[p2++];
	}
	for (int i = 0; i < 10 ; ++i)
	{
		a[i] = temp[i];
	}
}

//抽牌
void Shuffle1(vector<int>& arr, vector<int>& res)
{
	int k;
	for (int i = 0;i < arr.size();++i)
	{
		k = rand() % arr.size();
		res.push_back(arr[k]);
		arr.erase(arr.begin() + k);
	}
}
//洗牌
void Shuffle2(vector<int>& arr)
{
	int index;
	for (int i = 0; i < arr.size();++i)
	{
		index = rand() % arr.size();
		arr[i] ^= arr[index];
		arr[index] ^= arr[i];
		arr[i] ^= arr[index];
	}
}
