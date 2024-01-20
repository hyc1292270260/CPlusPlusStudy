#include <iostream>
#include <vector>
using namespace std;
//此算法适合最大值不大的情况，如果元素个数n不大，但是最大值很大，会造成空间浪费
void Count_Sort(vector<int> &arr, int n) {
	int len = arr.size();
	if (len < 1)
		return;
	vector<int> count(n + 1, 0);				////辅助数组count
	vector<int> temp(arr);						//辅助数组temp
	for (auto x : arr)							//遍历整个原始数组元素，将元素作为count的下标，统计每个元素出现的次数。
		count[x]++;
	for (int i = 1; i <= n; ++i)				//遍历count数组，对于每个元素x，计算出比x小的元素的个数
		count[i] += count[i - 1];
	for (int i = len - 1; i >= 0; --i) {
		arr[count[temp[i]] - 1] = temp[i];
		count[temp[i]]--;				//注意这里要减1
	}
}

int main()
{
	vector<int> a = { 4,2,1,6,9,8,6,7,4,3 };
	int n = 9;
	Count_Sort(a, n);
	for (auto x : a)
		cout << x << " ";
	cout << endl;
	return 0;
}
