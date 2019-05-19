// coding by 20150413 남윤원
// Graph Coloring

#include <iostream>
#include <iomanip>
using namespace std;

int n;	     // 정점의 개수
int m;       // 색의 개수
int *vcolor; // 결과값을 저장할 배열(포인터)
int **W;	 // 입력받을 비방향 그래프

void m_coloring(int i);
bool promising(int i);

int main()
{
	// 사용자로부터 비방향 그래프를 입력받는다.	
	cout << "지금부터 그래프 색칠하기 문제를 풀어 보겠습니다!" << endl;
	cout << "비방향 그래프를 입력해 주세요!" << endl;

	cout << "몇 개의 정점이 있나요? ";
	cin >> n;
	cout << "정점이 " << n << "개가 생성되었습니다!" << endl;

	// 입력받은 정점의 개수(n)대로 결과값을 저항할 배열(포인터) vcolor를 동적 할당한다.
	vcolor = new int[n + 1];

	// 입력받은 정점의 개수(n)대로 데이터를 입력받을 2차원 배열(이중 포인터) W를 동적 할당한다.
	W = new int*[n+1];
	for (int i = 1; i <= n; i++)
		W[i] = new int[n+1];

	cout << "이음선(edge)이 서로 인접해 있는지의 여부를 입력해 주세요!" << endl;
	cout << "인접해 있으면 1, 인접해 있지 않으면 0입니다."  << endl;
	cout << "자기 자신은 인접해 있지 않다고 가정하고, 0으로 입력하여 주세요." << endl;

	for (int i = 1; i <= n; i++) {
		cout << "V" << i << "에서 각 edge와 인접해 있는지 여부 : ";
		for (int j = 1; j <= n; j++)
		{
			cin >> W[i][j];
		}
	}

	// 사용자로부터 색깔을 입력받는다.
	cout << "몇 개의 색깔로 그래프를 칠하실 건가요? ";
	cin >> m;
	cout << m << "개의 색깔로 칠해 봅시다!" << endl;

	// 확인용 코드
	cout << endl << "W 배열 값 확인" << endl << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << setw(10) << W[i][j] << " ";
		cout << endl << endl;
	}

	// 함수 실행
	m_coloring(0);

	return 0;
}

// Algorithm 5.5 The Backtracking Algorithm for the m-Coloring Problem
// 문제 : 비방향그래프에서 m개의 색만 사용하여 인접한 정점이 같은 색이 되지 않게
//        정점을 색칠할 수 있는 모든 방법을 구하시오.
// 입력 : 양의 정수 n과 m, 그리고 n개의 정점을 가진 비방향그래프.
//        그래프는 행과 열의 인덱스가 모두 1부터 n까지인 2차원 배열 W로 표현된다.
//        여기서 i번째 정점과 j번째 정점 사이에 이음선이 존재하면 W[i][j]는 true이고,
//        그렇지 않으면 false이다.
// 출력 : 최대로 m개의 색을 가지고 인접한 정점이 같은 색이 되지 않게 그래프에 색칠하는 가능한 모든 경우.
//        출력은 인데스가 1부터 n까지인 배열 vcolor이다. 여기서 vcolor[i]값은 i번째 정점에 할당된 색
//        (1부터 m 사이의 정수)이다.
void m_coloring(int i)
{
	int color;
	if (promising(i))
		if (i == n) {
			cout << "조합 발견!" << endl;
			for(int i = 1; i <= n; i++)
				cout << vcolor[i] << " ";	// vcolor[1]에서 vcolor[n]까지
			cout << endl;
		}
		else
			for (color = 1; color <= m; color++) { // 다음 정점에 모든 색을 시도해 본다.
				vcolor[i + 1] = color;
				m_coloring(i + 1);
			}
}

bool promising(int i) {
	int j;
	bool switch_val;
	switch_val = true;
	j = 1;
	while (j < i && switch_val) {	// 인접한 정점에 이 색이 이미 칠해져 있는지 점검한다.
		if (W[i][j] && vcolor[i] == vcolor[j]) switch_val = false;
		j++;
	}
	return switch_val;
}