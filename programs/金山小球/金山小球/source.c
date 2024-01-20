#include<stdio.h>
int score(int balls[], int min_dex, int max_dex, char staff);
int main(void)
{
	int a[] = { 1,2,100,3 };
	int my_score = score(a, 0, 3, 'A');
	return 0;
}
int other_total_score;
int score(int balls[], int min_dex, int max_dex, char staff)
{
	char other_staff; int left_other_total_score; int right_other_total_score;
	int left_total_score; int right_total_score;
	//终止条件
	if (min_dex == max_dex)
	{
		other_total_score = 0;
		return balls[min_dex];
	}
	//换人
		other_staff = staff == 'A' ? 'B' : 'A';
   //测试左端利益
		left_other_total_score = score(balls, min_dex + 1, max_dex, other_staff);
		left_total_score = other_total_score;
	//测试右端利益
		right_other_total_score = score(balls, min_dex , max_dex-1, other_staff);
		right_total_score = other_total_score; 
	//做决定
		if ((left_total_score + balls[min_dex] - left_other_total_score) >= (right_other_total_score + balls[max_dex] - right_other_total_score))
		{
			other_total_score = left_other_total_score;
			return left_total_score + balls[min_dex];
		}
		else
		{
			other_total_score = right_other_total_score;
			return right_total_score + balls[max_dex];
		}
	
  









}

