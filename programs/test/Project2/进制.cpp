#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

//N的X进制和Y进制一起输出，判断N并输出十进制
//输入第一行是一个正整数（0，100] T 样例数
//每个样例，输入X，Y，Z，其中X和Y为进制[2,16]
//Z 是一个字符串 ， 长度为不超过62，表示正整数N[0，2^31-1]表示X进制和Y进制连接在一起
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
				if (isdigit(s1[j]))				//判断是不是十进制
				{
					sum1 += s1[j] - '0';
				}
				if (isalpha(s1[j]))			    //确定整数是否表示字母字符	
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