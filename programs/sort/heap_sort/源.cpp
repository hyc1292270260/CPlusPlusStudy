#include<stdio.h>
//time complexity O(nlog2^n)
//space complexity O(n)
//unstable
void exchange(int a[], int i, int j);
void heap_sort(int a[], int n);
void heapify(int a[], int root_pos, int last_pos);
void create_heap(int a[], int last_pos);
int main(void)
{

	int a[] = { 4,2,1,6,9,8,6,7,4,3 };
	heap_sort(a, sizeof a / sizeof a[0]);
	for (int i = 0; i < (sizeof a / sizeof a[0]); ++i)
		printf("%3i", a[i]);
	return 0;
}
void heap_sort(int a[], int n)
{
	create_heap(a, n - 1);
	for (int i = n - 1; i > 0; )
	{
		exchange(a, i, 0); 								//大顶堆堆顶交换到最后
		heapify(a, 0, --i);
	}
	return;
}
void heapify(int a[], int root_pos, int last_pos)

{
	int left = 2 * root_pos + 1, right = left + 1, max_pos = root_pos;
	if (left > last_pos)						// terminating condition
		return;
	if (a[left] > a[root_pos] /*&& left <= last_pos*/)					//find the max index
	{
		max_pos = left;
	}
	if (a[right] > a[max_pos] && right <= last_pos)
	{
		max_pos = right;
	}
	if (max_pos != root_pos)					//判断 max 是否发生变化
	{
		exchange(a, max_pos, root_pos);
		heapify(a, max_pos, last_pos);
	}

	return;

}
void create_heap(int a[], int last_pos)
{
	for (int i = (last_pos - 1) / 2; i >= 0; --i)				//从最后一个叶节点初始化堆
		heapify(a, i, last_pos);
	return;
}

void exchange(int a[], int i, int j)
{
	a[i] = a[i] ^ a[j];
	a[j] = a[i] ^ a[j];
	a[i] = a[i] ^ a[j];
	return;

}
//堆排序
void heapSort1(int arr[] )
{
	//构造大根堆
	int size = sizeof arr / sizeof arr[0];
	heapInsert(arr, size);
	
	while (size > 1) {
		//固定最大值
		exchange(arr, 0, size - 1);
		size--;
		//构造大根堆
		heapify(arr, 0, size);

	}

}

//构造大根堆（通过新插入的数上升）
void heapInsert(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		//当前插入的索引
		int currentIndex = i;
		//父结点索引
		int fatherIndex = (currentIndex - 1) / 2;
		//如果当前插入的值大于其父结点的值,则交换值，并且将索引指向父结点
		//然后继续和上面的父结点值比较，直到不大于父结点，则退出循环
		while (arr[currentIndex] > arr[fatherIndex]) {
			//交换当前结点与父结点的值
			exchange(arr, currentIndex, fatherIndex);
			//将当前索引指向父索引
			currentIndex = fatherIndex;
			//重新计算当前索引的父索引
			fatherIndex = (currentIndex - 1) / 2;
		}
	}
}
//将剩余的数构造成大根堆（通过顶端的数下降）
void heapify(int arr[] , int index, int size)
{
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	while (left < size) 
	{
		int largestIndex;
		//判断孩子中较大的值的索引（要确保右孩子在size范围之内）
		if (arr[left] < arr[right] && right < size) {
			largestIndex = right;
		}
		else {
			largestIndex = left;
		}
		//比较父结点的值与孩子中较大的值，并确定最大值的索引
		if (arr[index] > arr[largestIndex]) {
			largestIndex = index;
		}
		//如果父结点索引是最大值的索引，那已经是大根堆了，则退出循环
		if (index == largestIndex) {
			break;
		}
		//父结点不是最大值，与孩子中较大的值交换
		exchange(arr, largestIndex, index);
		//将索引指向孩子中较大的值的索引
		index = largestIndex;
		//重新计算交换之后的孩子的索引
		left = 2 * index + 1;
		right = 2 * index + 2;
	}

}

