// Algorithm 4.2 - Kruskal's Algorithm

#include "Kruskal's_algorithm.h"

// 문제 : 최소비용 신장트리를 구하시오.
// 입력 : 2보다 같거나 큰 정수 n, 양의 정수 m, n개의 마디와 m개의 이음선을 가진
//       연결된 가중치포함 비방향그래프
//       (이 그래프는 가중치와 함꼐 이음선이 포함된 집합 E로 표현한다.
// 출력 : 최소비용 신장트리에서 이음선의 집합 F
void Kruskal(int n, int m, set_of_edges E, set_of_edges F)
{
	int i, j;
	set_pointer p, q;
	int e;

	// E에 속한 m개의 이음선을 가중치가 작은 것부터 차례로 정렬한다.
	// 단, Worst Case에서 성능이 m*lg m이 나오도록 설계한다.
	quicksort(1, m, E);
	/*
	// F를 공집합으로 설정
	//F.Edges = NULL;
	//F.weight = NULL;
	*/
	initial(n); // n개의 서로소 부분집합을 초기화

	int s = 1;
	int add_F_count = 1;
	while (add_F_count < n) // F에서 이음선의 수는 n-1보다 작다. 즉 F에 n-1의 이음선이 있을 때 while루프를 빠져나간다.
	{
		e = E.weight[s]; // 아직 고려하지 않은 이음선 중 가중치가 최소인 이음선
		i = E.Edges[s][0]; // e로 연결된 마디의 인덱스
		j = E.Edges[s][1]; // e로 연결된 마디의 인덱스
		p = find(i);
		q = find(j);
		if (!equal(p, q))
		{
			merge(p, q);
			F.weight[add_F_count] = e;		// e를 F에 추가
			F.Edges[add_F_count][0] = i;	// i를 F에 추가
			F.Edges[add_F_count][1] = j;	// j를 F에 추가
			add_F_count++;
		}
		s++;
	}
}