// QuickSort 함수 구현

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "Disjoint_Set_Data_Structure.h"

void quicksort(int low, int high, set_of_edges& Result);
void partition(int low, int high, int& pivotpoint, set_of_edges& Result);

#endif