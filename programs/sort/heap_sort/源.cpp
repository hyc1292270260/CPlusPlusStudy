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
		exchange(a, i, 0); 								//�󶥶ѶѶ����������
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
	if (max_pos != root_pos)					//�ж� max �Ƿ����仯
	{
		exchange(a, max_pos, root_pos);
		heapify(a, max_pos, last_pos);
	}

	return;

}
void create_heap(int a[], int last_pos)
{
	for (int i = (last_pos - 1) / 2; i >= 0; --i)				//�����һ��Ҷ�ڵ��ʼ����
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
//������
void heapSort1(int arr[] )
{
	//��������
	int size = sizeof arr / sizeof arr[0];
	heapInsert(arr, size);
	
	while (size > 1) {
		//�̶����ֵ
		exchange(arr, 0, size - 1);
		size--;
		//��������
		heapify(arr, 0, size);

	}

}

//�������ѣ�ͨ���²������������
void heapInsert(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		//��ǰ���������
		int currentIndex = i;
		//���������
		int fatherIndex = (currentIndex - 1) / 2;
		//�����ǰ�����ֵ�����丸����ֵ,�򽻻�ֵ�����ҽ�����ָ�򸸽��
		//Ȼ�����������ĸ����ֵ�Ƚϣ�ֱ�������ڸ���㣬���˳�ѭ��
		while (arr[currentIndex] > arr[fatherIndex]) {
			//������ǰ����븸����ֵ
			exchange(arr, currentIndex, fatherIndex);
			//����ǰ����ָ������
			currentIndex = fatherIndex;
			//���¼��㵱ǰ�����ĸ�����
			fatherIndex = (currentIndex - 1) / 2;
		}
	}
}
//��ʣ���������ɴ���ѣ�ͨ�����˵����½���
void heapify(int arr[] , int index, int size)
{
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	while (left < size) 
	{
		int largestIndex;
		//�жϺ����нϴ��ֵ��������Ҫȷ���Һ�����size��Χ֮�ڣ�
		if (arr[left] < arr[right] && right < size) {
			largestIndex = right;
		}
		else {
			largestIndex = left;
		}
		//�Ƚϸ�����ֵ�뺢���нϴ��ֵ����ȷ�����ֵ������
		if (arr[index] > arr[largestIndex]) {
			largestIndex = index;
		}
		//�����������������ֵ�����������Ѿ��Ǵ�����ˣ����˳�ѭ��
		if (index == largestIndex) {
			break;
		}
		//����㲻�����ֵ���뺢���нϴ��ֵ����
		exchange(arr, largestIndex, index);
		//������ָ�����нϴ��ֵ������
		index = largestIndex;
		//���¼��㽻��֮��ĺ��ӵ�����
		left = 2 * index + 1;
		right = 2 * index + 2;
	}

}

