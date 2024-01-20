#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

//N��X���ƺ�Y����һ��������ж�N�����ʮ����
//�����һ����һ����������0��100] T ������
//ÿ������������X��Y��Z������X��YΪ����[2,16]
//Z ��һ���ַ��� �� ����Ϊ������62����ʾ������N[0��2^31-1]��ʾX���ƺ�Y����������һ��
using namespace std;
int main(void)
{
	int T;
	cin >> T;
	vector<int>result;
	while (T)
	{
		T--;
		int value1, value2;
		string s;
		cin >> value1 >> value2 >> s;

		int len = s.length();
		for (int i = 1; i < len; ++i)
		{
			string s1 = s.substr(0, i);
			string s2 = s.substr(i, len - i);
			int sum1 = 0, sum2 = 0;
			for (int j = 0; j < s1.length(); ++j)
			{
				sum1 *= value1;
				if (isdigit(s1[j]))				//�ж��ǲ���ʮ����
				{
					sum1 += s1[j] - '0';
				}
				if (isalpha(s1[j]))			    //ȷ�������Ƿ��ʾ��ĸ�ַ�	
				{
					sum1 += s1[j] - 'A' + 10;
				}
			}

			for (int j = 0; j < s2.length(); ++j)
			{
				sum2 *= value2;
				if (isdigit(s2[j]))
				{
					sum2 += s2[j] - '0';
				}
				if (isalpha(s2[j]))
				{
					sum2 += s2[j] - 'A' + 10;
				}
			}
			if (sum1 == sum2)
			{
				result.push_back(sum1);
				break;
			}
		}
	}
	for (int i : result)
	{
		cout << i << endl;
	}
	return 0;
}