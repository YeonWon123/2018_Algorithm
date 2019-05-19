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
typedef nodetype universe; // 전체집합은 1부터 n까지로 인덱스된다.

// 전역변수를 extern으로 선언하여, 다른 소스코드에서도 이 파일을 include할 경우 이 변수를 사용할 수 있음
extern universe *U;

struct set_of_edges {
	int **Edges;	// 각 이음선의 집합을 나타냄			ex) {(v1, v2), (v1, v3), (v1, v4), ...}
	int *weight;	// 각 이음선의 가중치의 집합을 나타냄	ex) { 3, 1, 5, ... }
};

// 함수 선언
void makeset(index i);
set_pointer find(index i);
void merge(set_pointer p, set_pointer q);
bool equal(set_pointer p, set_pointer q);
void initial(int size);

#endif