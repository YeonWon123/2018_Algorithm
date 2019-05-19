// Appendix C - Disjoint Set Data Structure II
// Disjoint_Set_Data_Structure.h에서 선언한 함수들을 정의합니다.

#include "Disjoint_Set_Data_Structure.h"

// 전역변수 선언
universe *U;

// 서로소 집합은 다음 호출로 만든다.
// for(int i = 0; i < n; i++) { makeset(i); }
// 이는 밑의 initial 함수에서 확인할 수 있다.

void makeset(index i)
{
	U[i].parent = i;
	U[i].depth = 0;
}

set_pointer find(index i)
{
	index j;

	j = i;
	while (U[j].parent != j)
		j = U[j].parent;
	return j;
}

void merge(set_pointer p, set_pointer q)
{
	if (U[p].depth == U[q].depth) {
		U[p].depth = U[p].depth + 1;		// 트리의 깊이는 증가해야 한다.
		U[q].parent = p;
	}
	else if (U[p].depth < U[q].depth)		// 깊이가 작은 트리를 자식마디로 만든다.
		U[p].parent = q;
	else
		U[p].parent = p;
}

bool equal(set_pointer p, set_pointer q)
{
	if (p == q)
		return true;
	else
		return false;
}

void initial(int size)
{
	U = new universe[size+1]; // n+1까지의 크기로 동적할당
	index i;

	for (i = 1; i <= size; i++)
		makeset(i);
}