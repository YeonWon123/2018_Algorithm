// Coding by 남윤원, 20150413
// Floyd's algorithm 구현 (구현언어 : C++)

#include <iostream>
#include <iomanip>
using namespace std;

// P는 전역(global) 배열로 정의한다.
// unsigned int 배열로 선언한 이유는, P에 -10000값을 입력할 때 언더플로우를 유도하여
// 최댓값이 저장되어 무한대의 수를 표현하기 용이하기 때문이다.
// P에 -1을 입력해서 unsigned int의 최댓값을 저장할 경우
// 이후의 D[i][k] + D[k][j]의 연산 중 오버플로우가 발생할 수 있으므로,
// P에 -10000을 입력하여 이 가능성을 줄이도록 유도한다.
unsigned int **P;

// Algorithm 3.4 floyd2
void floyd2(int n, unsigned int **W, unsigned int **D, unsigned int **P);

// Algorithm 3.5 path
void path(int q, int r);

int main()
{
	int Vertex;
	cout << "지금부터 Floyd의 알고리즘으로 최단경로를 알아보겠습니다!" << endl;
	cout << "몇 개의 마디(Vertex)가 있나요? ";
	cin >> Vertex;
	cout << "Vertex는 " << Vertex << "개가 생성되었습니다!" << endl;

	// 입력받은 Vertex의 크기대로 데이터를 입력받을 2차원 배열(이중 포인터) W를 동적 할당한다.
	unsigned int **W = new unsigned int*[Vertex];
	for (int i = 0; i < Vertex; i++)
		W[i] = new unsigned int[Vertex];

	cout << "이음선(edge)의 가중치(weight)를 입력해 주세요!" << endl;
	cout << "가중치(weight)가 무한대일 경우 -10000입니다." << endl;
	cout << "자기 자신의 가중치(weight)는 0으로 합니다." << endl;

	for (int i = 0; i < Vertex; i++) {
		cout << "V" << i + 1 << "에서 각 edge로 가는 weight : ";
		for (int j = 0; j < Vertex; j++)
			cin >> W[i][j];
	}

	// 확인용 코드
	cout << endl << "W 배열 값 확인" << endl << endl;
	for (int i = 0; i < Vertex; i++) {
		for (int j = 0; j < Vertex; j++)
			cout << setw(10) << W[i][j] << " ";
		cout << endl << endl;
	}

	// 최단 경로의 길이를 나타낼 2차원 배열(이중 포인터) D를 동적 할당한다.
	unsigned int **D = new unsigned int*[Vertex];
	for (int i = 0; i < Vertex; i++)
		D[i] = new unsigned int[Vertex];

	// 최단 경로를 나타낼 전역 2차원 배열(이중 포인터) P를 동적 할당한다.
	P = new unsigned int*[Vertex];
	for (int i = 0; i < Vertex; i++)
		P[i] = new unsigned int[Vertex];

	floyd2(Vertex, W, D, P);
	path(4, 1);
	cout << endl;
	return 0;
}

// Algorithm 3.4 floyd2
// 문제 : 가중치포함 그래프의 각 마디에서 다른 모든 마디로 가는 최단경로를 모두 계산함
//        여기에 더해서 최단경로도 찾음
// 입력 : 마디 개수가 n인 가중치포함 방향그래프, 그래프는 2차원 배열 W로 표현하는데, 
//        행과 열의 인덱스 범위는 1부터 n까지이다.
//        즉, W[i][j]는 정점 i에서 정점 j로 가는 이음선의 가중치이다.
// 출력 : 행과 열의 인덱스 범위가 1부터 n까지인 2차원 배열 D.
//        즉, D[i][j]는 정점 i에서 정점 j로 가는 최단경로의 길이가 된다.
//        여기에, 행과 열의 인덱스 범위가 모두 1부터 n까지인 배열 P 또한 출력이다.
void floyd2(int n, unsigned int **W, unsigned int **D, unsigned int **P)
{
	// cout << "floyd2 실행!!" << endl;

	int i, j, k;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			P[i][j] = 0;
	
	// cout << "D랑 W가 같다는거 선언할 거예요!" << endl;
	D = W;
	// cout << "D랑 W는 같아요!" << endl;
	/*
	cout << "D 배열 값 확인" << endl << endl;

	// 확인용 코드
	cout.setf(ios::right);
	for (int i = 0; i < n; i++)	{
		for (int j = 0; j < n; j++)
			cout << setw(10) << D[i][j] << " ";
		cout << endl;
		cout << endl;
	}
	*/
	for(k = 0; k < n; k++)
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				if (D[i][k] + D[k][j] < D[i][j]) {
					// 배열의 index는 0부터 시작하는데, 만약 index = 0일 경우,
					// 최단경로의 중간에 놓여있는 정점이 없는 경우도 0이므로 오해의 소지가 있다.
					// 이를 구분하기 위해 일단 k값에 1을 더한 값을 P[i][j]에 넣어준다.
					P[i][j] = k+1;	
					D[i][j] = D[i][k] + D[k][j];
				}

	cout << "D 배열 값 확인" << endl << endl;

	// 확인용 코드
	for (int i = 0; i < n; i++)	{
		for (int j = 0; j < n; j++)
			cout << setw(10) << D[i][j] << " ";
		cout << endl;
		cout << endl;
	}

	cout << "P 배열 값 확인" << endl << endl;

	// 확인용 코드
	for (int i = 0; i < n; i++)	{
		for (int j = 0; j < n; j++)
			cout << setw(10) << P[i][j] << " ";
		cout << endl;
		cout << endl;
	}

	// cout << "floyd2 완료!!" << endl << endl;
}


// Algorithm 3.5 path
// 문제 : 가중치포함 그래프에서 한 마디에서 다른 마디로 가는 최단경로 상에 있는
//        중간 마디들을 출력하시오.
// 입력 : 알고리즘 3.4가 만든 배열 P와 알고리즘 3.4의 입력인 그래프 마디의 인덱스 q와 r
// 재귀 호출할 때 값이 변하는 변수만 재귀 함수의 입력 파라미터로 하기로 하자.
// 그러므로, P는 전역(global) 배열로 정의한다.
void path(int q, int r)
{
	// 아까 k값에 1이 저장되어 있었으므로 다시 1을 빼주어야 한다.
	// 예를 들어, path(5,3)이 입력되었을 경우
	// 배열 상에서는 P[5-1][3-1] 즉 P[4][2]에 있는 값을 확인해야 한다.
	if (P[q-1][r-1] != 0) {
		path(q, P[q-1][r-1]);
		cout << "v" << P[q-1][r-1] << "    ";
		path(P[q-1][r-1], r);
	}
}