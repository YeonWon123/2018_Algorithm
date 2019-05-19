#include <iostream>
using namespace std;

#define SIZE 9

int S[SIZE] = { -1, 15, 22, 13, 27, 12, 10, 20, 25 };

void quicksort(int low, int high);
void partition(int low, int high, int& pivotpoint);

void quicksort(int low, int high)
{
	int pivotpoint;

	if (high > low) {
		partition(low, high, pivotpoint);
		quicksort(low, pivotpoint - 1);
		quicksort(pivotpoint + 1, high);
	}
}

void partition(int low, int high, int& pivotpoint)
{
	int i, j, temp;
	int pivotitem;
	
	pivotitem = S[low]; // pivotitem으로 첫 원소 선택
	j = low;
	for (i = low + 1; i <= high; i++) {
		if (S[i] < pivotitem) {
			j++;
			// exchange S[i] and S[j];
			temp = S[i];
			S[i] = S[j];
			S[j] = temp;
		}
	}
	pivotpoint = j;

	// exchange S[low] and S[pivotpoint]; // pivotitem 값을 pivotpoint에 저장
	temp = S[low];
	S[low] = S[pivotpoint];
	S[pivotpoint] = temp;
}


int main()
{
	cout << "quicksort 전" << "\n";
	for (int i = 1; i < SIZE; i++)
	{
		cout << "S[" << i << "]: " << S[i] << "\n";
	}

	quicksort(1, 8);

	cout << "quicksort 후" << "\n";
	for (int i = 1; i < SIZE; i++)
	{
		cout << "S[" << i << "]: " << S[i] << "\n";
	}

}