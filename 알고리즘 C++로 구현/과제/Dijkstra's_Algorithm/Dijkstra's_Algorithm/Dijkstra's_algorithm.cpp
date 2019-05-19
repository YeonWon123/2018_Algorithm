// coding by 남윤원, 20150413
// Dijkstra's Algorithm for Single-Source Shortest Paths

#include <iostream>
#include <iomanip>
using namespace std;

// 이음선을 나타내는 구조체
struct edge {
	int index[2];	// (v1, v2)를 표현 (출발지와 목적지를 표현)
	int weight;		// 가중치를 표현
};

// 이음선의 집합 구조체
struct set_of_edges {
	edge *edge_i;	// edge형 배열(포인터) 선언
};

// Algorithm 4.3 - Dijkstra's Algorithm
// 문제 : 가중치포함 방향그래프에서 v1에서 다른 모든 마디로 가는 최단경로를 구하시오.
// 입력 : 정수 n(>=2)와 마디가 n개 있는 연결된 가중치포함 방향그래프. 
//        이 그래프는 이차원 배열 W로 표현되며, 행과 열의 인덱스는 각각 1부터 n까지이다.
//        여기서 W[i][j]는 i번째 마디에서 j번째 마디를 잇는 이음선 상의 가중치가 된다.
// 출력 : 최단경로 상에 놓여있는 이음선의 집합 F
void dijkstra(int n, int **W, set_of_edges& F)
{
	int i, vnear, s;
	edge e;
	int *touch;	// touch[i] = Y에 속한 마디들만 중간에 거치도록 하여 v1에서 vi로 가는 현재 최단경로 상의
				//            마지막 이음선은 <v,vi>라고 할 때, Y에 속한 마디 v의 인덱스
	touch = new int[n+1];
	int *length;	// length[i] = Y에 속한 마디들만 중간에 거치도록 하여 v1에서 vi로 가는 현재 최단경로의 길이
	length = new int[n+1];

	// F는 공집합
	for (i = 2; i <= n; i++) {	// 각 마디에 대해서
		touch[i] = 1;				// v1에서 출발하는 현재 최단경로의 마지막 마디를
		length[i] = W[0][i-1];		// v1으로 초기화한다.

		if (W[0][i-1] == -1)
			length[i] = 987654321;	// 엄청 큰 수로 설정

	}								// 그 경로의 길이는 v1에서의 이음선 상의 가중치로
									// 초기화한다.
	
	// 확인용 코드
	/*
	cout << "touch와 length[i] 까지 완료!" << endl;
	for (int j = 0; j <= n; j++)
	{
		cout << "touch[" << j << "]: " << touch[j] << endl;
		cout << "length[" << j << "]: " << length[j] << endl;
	}
	*/
	for(s = 1; s <= n - 1; s++) {	// n-1번 반복
		// cout << "반복 시작!" << endl;
		// cout << "s값은 " << s << endl;
		int min = 987654321; // 엄청 큰 수로 설정
		for (i = 2; i <= n; i++) {	// 최단경로를 가지는지 각 마디를 점검한다.
			if ((0 < length[i]) && (length[i] < min)) {
				min = length[i];
				vnear = i;
			}
		}

		// e = touch[vnear]가 인덱스인 마디에서 vnear가 인덱스인 마디로 가는 이음선;
		e.index[0] = touch[vnear];
		e.index[1] = vnear;
		e.weight = min;
		// e를 F에 추가;
		F.edge_i[s].index[0] = e.index[0];
		F.edge_i[s].index[1] = e.index[1];
		F.edge_i[s].weight = min;

		// cout << "e를 F에 추가!" << endl;

		for (i = 2; i <= n; i++) {
			// cout << "i의 값 " << i << endl;
			// cout << "vnear의 값 " << vnear << endl;
			if (W[vnear - 1][i - 1] != -1 && length[vnear] != -1) {
				if (length[vnear] + W[vnear - 1][i - 1] < length[i]) {
					length[i] = length[vnear] + W[vnear - 1][i - 1];
					// cout << "length[i]에 할당 성공! length[i] " << length[i] << endl;
					touch[i] = vnear;			// Y에 속하지 않는 각 마디에 대해서,
					// cout << "touch[i]에 할당 성공! touch[i] " << touch[i] << endl;
				}								// 최단경로를 바꾼다.
			}
		}

		length[vnear] = -1;				// vnear가 인덱스인 마디를 Y에 추가한다.
		// cout << "length[vnear]에 할당 성공! length[vnear] " << length[vnear] << endl;
		// cout << "하나 끝!" << endl;
	}
}

int main()
{
	// 사용자로부터 그래프를 입력받는다.	
	int Vertex;		// 정점(마디)의 개수
	cout << "지금부터 단일출발점 최단경로 문제를 풀어 보겠습니다!" << endl;
	cout << "단일출발점 최단경로 문제를 풀 그래프를 입력해 주세요!" << endl;

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
		}
	}


	// 확인용 코드
	cout << endl << "W 배열 값 확인" << endl << endl;
	for (int i = 0; i < Vertex; i++) {
		for (int j = 0; j < Vertex; j++)
			cout << setw(10) << W[i][j] << " ";
		cout << endl << endl;
	}


	set_of_edges output;
	output.edge_i = new edge[Vertex];

	// cout << "다익스트라 함수 호출 시작!" << endl;
	// 다익스트라 함수 호출
	dijkstra(Vertex, W, output);
	// cout << "다익스트라 함수 호출 끝!" << endl;	

	// 집합 F 출력
	cout << endl << "이음선의 집합은 다음과 같습니다!" << endl << endl;
	for (int i = 1; i < Vertex; i++)
	{
		cout << i << "번째 output.edges" << endl;
		cout << output.edge_i[i].index[0] << " " << output.edge_i[i].index[1] << endl;
		cout << i << "번째 output.weight" << endl;
		cout << output.edge_i[i].weight << endl;
	}
}