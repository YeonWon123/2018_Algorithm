// Appendix C - Disjoint Set Data Structure II

#ifndef DISJOINT_SET_DATA_STRUCTURE_H
#define DISJOINT_SET_DATA_STRUCTURE_H

#include <iostream>
using namespace std;

typedef int index;
typedef index set_pointer;

struct nodetype
{
	index parent;
	int depth;
};
typedef nodetype universe; // ��ü������ 1���� n������ �ε����ȴ�.

// ���������� extern���� �����Ͽ�, �ٸ� �ҽ��ڵ忡���� �� ������ include�� ��� �� ������ ����� �� ����
extern universe *U;

struct set_of_edges {
	int **Edges;	// �� �������� ������ ��Ÿ��			ex) {(v1, v2), (v1, v3), (v1, v4), ...}
	int *weight;	// �� �������� ����ġ�� ������ ��Ÿ��	ex) { 3, 1, 5, ... }
};

// �Լ� ����
void makeset(index i);
set_pointer find(index i);
void merge(set_pointer p, set_pointer q);
bool equal(set_pointer p, set_pointer q);
void initial(int size);

#endif