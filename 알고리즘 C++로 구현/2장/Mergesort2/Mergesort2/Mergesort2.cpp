#include <iostream>
using namespace std;

#define SIZE 9

// 배열을 전역으로 선언
int S[SIZE] = { -1, 27, 10, 12, 20, 25, 13, 15, 22 };
void mergesort2(int low, int high);
void merge2(int low, int mid, int high);

void mergesort2(int low, int high)
{
	int mid;

	if (low < high) {
		mid = (low + high) / 2;
		mergesort2(low, mid);
		mergesort2(mid + 1, high);
		merge2(low, mid, high);
	}
}

void merge2(int low, int mid, int high)
{
	// cout << "merge2 실행!" << endl;
	int i, j, k;
	// 정적 배열로 구현	
	// int U[9] = { 0 };

	// 동적 배열로 구현해보기
	int* U = new int[high+1];   // 합병에 필요한 지역 배열, 동적으로 생성
	i = low; j = mid + 1; k = low;

	// cout << "i의 값:" << i << ", j의 값: " << j << ", k의 값: " << k << endl;
	// cout << "low의 값: " << low << ", mid의 값: " << mid << ", high의 값: " << high << endl;
	while (i <= mid && j <= high) {
		if (S[i] < S[j]) {
			U[k] = S[i];
			i++;
		}
		else {
			U[k] = S[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		// move S[j] through S[high] to U[k] through U[high];
		for (; j <= high; j++)
		{
			int p = 0;
			U[k+p] = S[j];
			p++;
		}
	}
	else {
		// move S[i] through S[mid] to U[k] through U[high];
		for (; i <= mid; i++)
		{
			int p = 0;
			U[k+p] = S[i];
			p++;
		}
	}
	// move U[low] through U[high] to S[low] through S[high];
	for (int p = low; p <= high; p++)
	{
		S[p] = U[p];
		// cout << "S[" << p << "]:" << S[p] << endl;
	}

	delete[] U;
}

int main()
{
	for (int i = 1; i < SIZE; i++) {
		cout << "정렬 전 S[" << i << "]: " << S[i] << endl;
	}

	mergesort2(1, 8);

	cout << endl;

	for (int i = 1; i < SIZE; i++) {
		cout << "정렬 후 S[" << i << "]: " << S[i] << endl;
	}

	return 0;
}