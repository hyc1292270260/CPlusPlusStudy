#include <iostream>
#include <vector>
using namespace std;
//���㷨�ʺ����ֵ�������������Ԫ�ظ���n���󣬵������ֵ�ܴ󣬻���ɿռ��˷�
void Count_Sort(vector<int> &arr, int n) {
	int len = arr.size();
	if (len < 1)
		return;
	vector<int> count(n + 1, 0);				////��������count
	vector<int> temp(arr);						//��������temp
	for (auto x : arr)							//��������ԭʼ����Ԫ�أ���Ԫ����Ϊcount���±꣬ͳ��ÿ��Ԫ�س��ֵĴ�����
		count[x]++;
	for (int i = 1; i <= n; ++i)				//����count���飬����ÿ��Ԫ��x���������xС��Ԫ�صĸ���
		count[i] += count[i - 1];
	for (int i = len - 1; i >= 0; --i) {
		arr[count[temp[i]] - 1] = temp[i];
		count[temp[i]]--;				//ע������Ҫ��1
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
