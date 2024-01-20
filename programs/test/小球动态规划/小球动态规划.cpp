#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct _Score
{
	int A_score = 0;
	int B_score = 0;
}Score;

int result_A[500] = { 0 };
int result_B[500] = { 0 };
Score CalScore(
	int chessman[],
	int left,
	int right,
	int current_index_A,
	int current_index_B,
	char current_staff);

int main(void)
{
	int N;
	int chessman[1000] = { 0 };
	scanf("%i", &N);
	for (int i = 0; i < N; ++i)
		scanf("%i", &chessman[i]);

	Score score = CalScore(chessman, 0, N - 1, 0, -1, 'A');
	printf("%i %i", score.A_score, score.B_score);
	return 0;
}

int Calculate(int chessman[], int n)
{
	if (!chessman)
		return 0;

	int result = chessman[0];

	for (int i = 1; i <= n; ++i)
		result += abs(chessman[i] - chessman[i-1]);
	return result;
}

Score CalScore(
	int chessman[],
	int left,
	int right,
	int current_index_A,
	int current_index_B,
	char current_staff)
{
	Score total_score = { 0 };
	if (!chessman)
		return total_score;

	// terminal condition.
	if (left == right)
	{
		if (current_staff == 'A')
		{
			result_A[current_index_A] = chessman[left];
			total_score.A_score = Calculate(result_A, current_index_A);
			total_score.B_score = Calculate(result_B, current_index_B);
		}
		else
		{
			result_B[current_index_B] = chessman[left];
			total_score.A_score = Calculate(result_A, current_index_A);
			total_score.B_score = Calculate(result_B, current_index_B);
		}
		return total_score;
	}

	Score temp_left = { 0 }, temp_right = { 0 };
	if (current_staff == 'A')
	{
		// left.
		result_A[current_index_A] = chessman[left];
		temp_left = CalScore(chessman, left + 1, right, current_index_A, current_index_B + 1, 'B');
		// right.
		result_A[current_index_A] = chessman[right];
		temp_right = CalScore(chessman, left, right - 1, current_index_A, current_index_B + 1, 'B');

		if (temp_left.A_score >= temp_right.A_score)
			return temp_left;
		else
			return temp_right;
	}
	else
	{
		// left.
		result_B[current_index_B] = chessman[left];
		temp_left = CalScore(chessman, left + 1, right, current_index_A + 1, current_index_B, 'A');
		// right.
		result_B[current_index_B] = chessman[right];
		temp_right = CalScore(chessman, left, right - 1, current_index_A + 1, current_index_B, 'A');

		if (temp_left.B_score >= temp_right.B_score)
			return temp_left;
		else
			return temp_right;
	}
}