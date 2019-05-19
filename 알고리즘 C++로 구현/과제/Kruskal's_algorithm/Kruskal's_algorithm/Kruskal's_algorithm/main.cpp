// coding by 남윤원, 20150413 
// Kruskal's Algorithm
// 구현 언어 : C++

#include "Disjoint_Set_Data_Structure.h"
#include "Kruskal's_algorithm.h"
#include "QuickSort.h"
#include <iomanip>

int main()
{
	// ---------------------------------------------------------------------------------
	// 1. 사용자로부터 그래프를 입력받는다. 이때 이음선의 수를 count한다.
	// ---------------------------------------------------------------------------------

	int Vertex;		// 정점(마디)의 개수
	int Edge_count = 0;	// 이음선의 개수
	cout << "지금부터 최소비용 신장트리(MST)를 구해보겠습니다!" << endl;
	cout << "최소비용 신장트리를 구할 그래프를 입력해 주세요!(단, 비방향성 그래프여야 합니다.)" << endl;

	cout << "몇 개의 마디(Vertex)가 있나요? ";
	cin >> Vertex;
	cout << "Vertex는 " << Vertex << "개가 생성되었습니다!" << endl;

	// 입력받은 Vertex의 크기대로 데이터를 입력받을 2차원 배열(이중 포인터) W를 동적 할당한다.
	int **W = new int*[Vertex];
	for (int i = 0; i < Vertex; i++)
		W[i] = new int[Vertex];

	cout << "이음선(edge)의 가중치(weight)를 입력해 주세요!" << endl;
	cout << "가중치(weight)가 무한대일 경우 -1입니다." << endl;
	cout << "자기 자신의 가중치(weight)는 0으로 합니다." << endl;

	for (int i = 0; i < Vertex; i++) {
		cout << "V" << i + 1 << "에서 각 edge로 가는 weight : ";
		for (int j = 0; j < Vertex; j++)
		{
			cin >> W[i][j];
			if (W[i][j] > 0) // 가중치가 0이 아닐 경우 이음선이 있다는 것이므로
				Edge_count++;		 // Edge를 1 증가시킨다.
		}
	}
	
	Edge_count = Edge_count / 2; // 비방향성 그래프이므로, Edge는 2번씩 세어졌으므로 나누기 2를 해준다.

	// 확인용 코드
	cout << endl << "W 배열 값 확인" << endl << endl;
	for (int i = 0; i < Vertex; i++) {
		for (int j = 0; j < Vertex; j++)
			cout << setw(10) << W[i][j] << " ";
		cout << endl << endl;
	}
	

	// ---------------------------------------------------------------------------------
	// 2. 입력받은 그래프에서, 이음선과 그 가중치를, set_of_edges 구조체 변수 안에 넣는다.
	// ---------------------------------------------------------------------------------

	// 먼저 set_of_edges 구조체변수를 생성한다.
	set_of_edges input;
	
	// 위에서 선언한 구조체변수(input) 안의 배열(포인터)들을 Edge의 개수+1만큼 동적할당해준다.
	// Edge의 개수+1만큼 동적할당해주는 이유는 인덱스를 1부터 사용할 것이기 때문이다.
	// 이 때, weight와 Edges 각각에 따로 동적 할당해준다.
	input.weight = new int[Edge_count+1];
	input.Edges = new int*[Edge_count+1];
	for (int i = 1; i <= Edge_count; i++)
		input.Edges[i] = new int[2];     // (v1, v2)와 같이 표현하기 위해서는 배열의 크기가 2라면 충분하다.

	// 이제 입력받은 그래프에서 이음선과 그 가중치를 input에 넣는다.
	int k = 1;	// input.weight와 input.Edges의 인덱스를 1부터 시작
	for (int i = 0; i < Vertex; i++)
	{
		for (int j = i+1; j < Vertex; j++)
		{
			if (W[i][j] > 0)
			{
				input.weight[k] = W[i][j];
				input.Edges[k][0] = i+1;
				input.Edges[k][1] = j+1;
				k++;
			}
		}
	}
	/*
	// 확인용 코드
	for (int i = 1; i <= Edge_count; i++)
	{
		cout << i << "번째 input.Edges" << endl;
		cout << input.Edges[i][0] << " " << input.Edges[i][1] << endl;
		cout << i << "번째 input.weight" << endl;
		cout << input.weight[i] << endl;
	}
	*/


	// ---------------------------------------------------------------------------------
	// 3. Kruskal's algorithm을 이용하여 최소비용 신장트리(MST)를 구한다.
	// ---------------------------------------------------------------------------------

	// output는 MST에서 이음선의 집합을 저장하는 변수가 될 것이다.
	// MST에서 이음선의 수는 Vertex-1이므로, F에 Vertex-1의 크기만큼 동적 할당해준다.
	// 이 때, weight와 Edges 각각에 따로 동적 할당해준다.
	set_of_edges output;
	output.weight = new int[Vertex];
	output.Edges = new int*[Vertex];
	for (int i = 1; i < Vertex; i++)
		output.Edges[i] = new int[2];	// (v1, v2)와 같이 표현하기 위해서는 배열의 크기가 2라면 충분하다.

	// 크루스칼 알고리즘을 적용하여 output에 결과값이 저장되게 한다.
	// 즉 MST에서 이음선의 집합이 output에 저장되게 한다.
	Kruskal(Vertex, Edge_count, input, output);

	// MST에서, 이음선의 집합이 저장된 output을 출력해 본다.

	cout << endl << "이음선의 집합은 다음과 같습니다!" << endl << endl;
	for (int i = 1; i < Vertex; i++)
	{
		cout << i << "번째 output.Edges" << endl;
		cout << output.Edges[i][0] << " " << output.Edges[i][1] << endl;
		cout << i << "번째 output.weight" << endl;
		cout << output.weight[i] << endl;
	}
}