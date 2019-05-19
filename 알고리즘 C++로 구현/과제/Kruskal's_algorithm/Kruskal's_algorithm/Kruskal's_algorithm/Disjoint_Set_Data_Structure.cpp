// Appendix C - Disjoint Set Data Structure II
// Disjoint_Set_Data_Structure.h���� ������ �Լ����� �����մϴ�.

#include "Disjoint_Set_Data_Structure.h"

// �������� ����
universe *U;

// ���μ� ������ ���� ȣ��� �����.
// for(int i = 0; i < n; i++) { makeset(i); }
// �̴� ���� initial �Լ����� Ȯ���� �� �ִ�.

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
		U[p].depth = U[p].depth + 1;		// Ʈ���� ���̴� �����ؾ� �Ѵ�.
		U[q].parent = p;
	}
	else if (U[p].depth < U[q].depth)		// ���̰� ���� Ʈ���� �ڽĸ���� �����.
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
	U = new universe[size+1]; // n+1������ ũ��� �����Ҵ�
	index i;

	for (i = 1; i <= size; i++)
		makeset(i);
}