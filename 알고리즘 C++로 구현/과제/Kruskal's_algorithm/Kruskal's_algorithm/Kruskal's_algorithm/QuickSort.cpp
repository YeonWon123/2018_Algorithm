// QuickSort �Լ� ����

#include "QuickSort.h"

void quicksort(int low, int high, set_of_edges& Result)
{
	int pivotpoint;

	if (high > low) {
		partition(low, high, pivotpoint, Result);
		quicksort(low, pivotpoint - 1, Result);
		quicksort(pivotpoint + 1, high, Result);
	}
}

void partition(int low, int high, int& pivotpoint, set_of_edges& Result)
{
	int i, j, temp;
	int* temp_pointer;
	int pivotitem;

	pivotitem = Result.weight[low]; // pivotitem���� ù ���� ����
	j = low;
	for (i = low + 1; i <= high; i++) {
		if (Result.weight[i] < pivotitem) {
			j++;
			// exchange Result.weight[i] and Result.weight[j];
			temp = Result.weight[i];
			Result.weight[i] = Result.weight[j];	
			Result.weight[j] = temp;
	
			// exchange Result.Edges[i] and Result.Edges[j];
			temp_pointer = Result.Edges[i];
			Result.Edges[i] = Result.Edges[j];
			Result.Edges[j] = temp_pointer;
		}
	}
	pivotpoint = j;

	// exchange Result.weight[low] and Result.weight[pivotpoint]; // pivotitem ���� pivotpoint�� ����
	// exchange Result.Edges[low] and Result.Edges[pivotpoint];
	temp = Result.weight[low];
	Result.weight[low] = Result.weight[pivotpoint];
	Result.weight[pivotpoint] = temp;

	temp_pointer = Result.Edges[low];
	Result.Edges[low] = Result.Edges[pivotpoint];
	Result.Edges[pivotpoint] = temp_pointer;
}