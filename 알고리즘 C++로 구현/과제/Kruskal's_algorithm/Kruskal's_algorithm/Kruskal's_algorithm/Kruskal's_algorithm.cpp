// Algorithm 4.2 - Kruskal's Algorithm

#include "Kruskal's_algorithm.h"

// ���� : �ּҺ�� ����Ʈ���� ���Ͻÿ�.
// �Է� : 2���� ���ų� ū ���� n, ���� ���� m, n���� ����� m���� �������� ����
//       ����� ����ġ���� �����׷���
//       (�� �׷����� ����ġ�� �Բ� �������� ���Ե� ���� E�� ǥ���Ѵ�.
// ��� : �ּҺ�� ����Ʈ������ �������� ���� F
void Kruskal(int n, int m, set_of_edges E, set_of_edges F)
{
	int i, j;
	set_pointer p, q;
	int e;

	// E�� ���� m���� �������� ����ġ�� ���� �ͺ��� ���ʷ� �����Ѵ�.
	// ��, Worst Case���� ������ m*lg m�� �������� �����Ѵ�.
	quicksort(1, m, E);
	/*
	// F�� ���������� ����
	//F.Edges = NULL;
	//F.weight = NULL;
	*/
	initial(n); // n���� ���μ� �κ������� �ʱ�ȭ

	int s = 1;
	int add_F_count = 1;
	while (add_F_count < n) // F���� �������� ���� n-1���� �۴�. �� F�� n-1�� �������� ���� �� while������ ����������.
	{
		e = E.weight[s]; // ���� ������� ���� ������ �� ����ġ�� �ּ��� ������
		i = E.Edges[s][0]; // e�� ����� ������ �ε���
		j = E.Edges[s][1]; // e�� ����� ������ �ε���
		p = find(i);
		q = find(j);
		if (!equal(p, q))
		{
			merge(p, q);
			F.weight[add_F_count] = e;		// e�� F�� �߰�
			F.Edges[add_F_count][0] = i;	// i�� F�� �߰�
			F.Edges[add_F_count][1] = j;	// j�� F�� �߰�
			add_F_count++;
		}
		s++;
	}
}