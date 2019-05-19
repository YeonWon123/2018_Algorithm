#include <iostream>
using namespace std;

#define SIZE 9

// �迭�� �������� ����
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
	// cout << "merge2 ����!" << endl;
	int i, j, k;
	// ���� �迭�� ����	
	// int U[9] = { 0 };

	// ���� �迭�� �����غ���
	int* U = new int[high+1];   // �պ��� �ʿ��� ���� �迭, �������� ����
	i = low; j = mid + 1; k = low;

	// cout << "i�� ��:" << i << ", j�� ��: " << j << ", k�� ��: " << k << endl;
	// cout << "low�� ��: " << low << ", mid�� ��: " << mid << ", high�� ��: " << high << endl;
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
		cout << "���� �� S[" << i << "]: " << S[i] << endl;
	}

	mergesort2(1, 8);

	cout << endl;

	for (int i = 1; i < SIZE; i++) {
		cout << "���� �� S[" << i << "]: " << S[i] << endl;
	}

	return 0;
}