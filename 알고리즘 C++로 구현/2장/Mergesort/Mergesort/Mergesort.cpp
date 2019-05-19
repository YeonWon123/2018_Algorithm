#include <iostream>
using namespace std;

#define SIZE 8

void mergesort(int n, int S[]);
void merge(int h, int m, const int U[], const int V[], int S[]);


void mergesort(int n, int S[])
{
	if (n > 1) {
		const int h = n / 2;
		const int m = n - h;
		int *U = new int[h];
		int *V = new int[m];

		for (int i = 0; i < h; i++) {
			U[i] = S[i];
			V[i] = S[h + i];
		}
		
		mergesort(h, U);
		mergesort(m, V);
		merge(h, m, U, V, S);
	}
}

void merge(int h, int m, const int U[], const int V[], int S[])
{
	int i, j, k;

	i = 0; j = 0; k = 0;
	while (i < h && j < m) {
		if (U[i] < V[j]) {
			S[k] = U[i];
			i++;
		}
		else {
			S[k] = V[j];
			j++;
		}
		k++;
	}
	if (i > h) {
		for (; j < m; j++) {
			int p = 0;
			S[k+p] = V[j];
			p++;
		}
	}
	else {
		for (; i < h; i++) {
			int p = 0;
			S[k+p] = U[i];
			p++;
		}
	}
}

int main()
{
	int arr[SIZE] = { 27,10,12,20,25,13,15,22 };
	mergesort(SIZE, arr);

	for(int i = 0; i < SIZE; i++)
		cout << "arr[" << i << "]: " << arr[i] << endl;

	return 0;
}