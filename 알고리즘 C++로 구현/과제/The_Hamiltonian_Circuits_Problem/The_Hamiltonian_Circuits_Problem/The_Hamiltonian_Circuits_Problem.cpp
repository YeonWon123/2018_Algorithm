// coding by 20150413 남윤원
// The Hamiltonian Circuits Problem

#include <iostream>
using namespace std;

int n;			// 정점의 개수(양의 정수)
int **W;		// 입력받은 비방향 그래프
int *vindex;	// 결과값을 저장할 배열(포인터)

void hamiltonian(int i);
bool promising(int i);


int main()
{
	// 사용자로부터 비방향 그래프를 입력받는다.	
	cout << "지금부터 해밀튼 회로 문제를 풀어 보겠습니다!" << endl;
	cout << "비방향 그래프를 입력해 주세요!" << endl;

	cout << "몇 개의 정점이 있나요? ";
	cin >> n;
	cout << "정점이 " << n << "개가 생성되었습니다!" << endl;

	// 입력받은 정점의 개수(n)대로 결과값을 저항할 배열(포인터) vcolor를 동적 할당한다.
	vindex = new int[n];

	// 입력받은 정점의 개수(n)대로 데이터를 입력받을 2차원 배열(이중 포인터) W를 동적 할당한다.
	W = new int*[n + 1];
	for (int i = 1; i <= n; i++)
		W[i] = new int[n + 1];

	cout << "이음선(edge)이 서로 인접해 있는지의 여부를 입력해 주세요!" << endl;
	cout << "인접해 있으면 1, 인접해 있지 않으면 0입니다." << endl;
	cout << "자기 자신은 인접해 있지 않다고 가정하고, 0으로 입력하여 주세요." << endl;

	for (int i = 1; i <= n; i++) {
		cout << "V" << i << "에서 각 edge와 인접해 있는지 여부 : ";
		for (int j = 1; j <= n; j++)
		{
			cin >> W[i][j];
		}
	}

	// 함수 호출
	vindex[0] = 1;	// v1을 출발정점으로 한다.
	hamiltonian(0);

	return 0;
}

// Algorithm 5.6 The Backtracking Algorithm for the Hamiltonian Circuits Problem
// 문제 : 연결된 비방향그래프에서 해밀튼 회로를 모두 구하시오.
// 해밀턴 경로 : 한 정점에서 출발하여, 다른 모든 정점을 한번씩 거치고, 다시 시작 정점으로 돌아오는 경로
// 입력 : 양의 정수 n과 정점이 n개인 비방향그래프. 그래프는 2차원 배열 W로 표현한다.
//        이 배열의 행과 열의 인덱스는 1부터 n까지이다. 여기서 i째 정점과 j째 정점을 잇는 이음선이 있으면
//        W[i][j] 값은 true이고, 그렇지 않으면 false이다.
// 출력 : 주어진 정점에서 출발하여 그래프상의 각 정점을 정확히 한 번씩 방문하고, 출발 정점으로 돌아오는 모든 경로.
//        각 경로의 출력은 인덱스가 0부터 n-1까지인 인덱스의 배열 vindex이다.
//        여기서 vindex[i]는 경로상에서 i째 정점의 인덱스이다.
//        출발 정점의 인덱스는 vindex[0]이다.
void hamiltonian(int i)
{
	int j;

	if (promising(i))
		if (i == n - 1) {
			cout << "해밀턴 회로를 찾았다!" << endl;
			for(int i = 0; i < n; i++)
				cout << vindex[i] << " ";
			cout << endl;
		}
		else
			for (j = 2; j <= n; j++) {	// 모든 정점의 다음 정점을 시도해 본다.
				vindex[i + 1] = j;
				hamiltonian(i + 1);
			}
}

bool promising(int i)
{
	int j;
	bool switch_val;

	if (i == n - 1 && !W[vindex[n - 1]][vindex[0]]) // 첫째 정점을 마지막 정점과
		switch_val = false;							// 인접해야 하고,
	else if (i > 0 && !W[vindex[i - 1]][vindex[i]])	// i째 정점은 (i-1)째 정점과
		switch_val = false;							// 인접해야 한다.
	else {
		switch_val = true;
		j = 1;
		while (j < i && switch_val) {				// 정점이 이미 선택되었는지를 검사한다.
			if (vindex[i] == vindex[j])
				switch_val = false;
			j++;
		}
	}
	return switch_val;
}