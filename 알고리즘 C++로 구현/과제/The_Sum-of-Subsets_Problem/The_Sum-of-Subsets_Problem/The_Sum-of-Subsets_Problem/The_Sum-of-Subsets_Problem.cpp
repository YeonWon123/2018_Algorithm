// coding by 남윤원, 20150413
// The Backtracking Algorithm for the Sum-of-Subsets Problem

#include <iostream>
using namespace std;

// 관습에 따라서, n, *w, W, *include는 이 프로시저의 입력이 아니다.
// 즉, 이 변수들을 전역적으로 정의한다.
int n;			// 양의 정수의 개수
int *w;			// (감소하지 않는 순으로) 정렬된 양의 정수의 배열 (범위는 1부터 n)
int W;			// 묙표로 하는 양의 정수 W
int *include;	// 결과값이 저장될 배열

// 함수 원형 정의
void sum_of_subsets(int i, int weight, int total);
bool promising(int i, int weight, int total);


int main()
{
	int total = 0;
	cout << "지금부터 부분집합의 합 구하기 문제를 풀어 보겠습니다!" << endl;
	cout << "이 프로그램은, 합이 W가 되는 모든 정수의 조합을 구하게 됩니다." << endl;
	cout << "목표로 하는 양의 정수 W를 입력하세요!" << endl;
	cin >> W;
	cout << "목표로 하는 양의 정수 W는 " << W << " 입니다!" << endl;
	cout << "다음으로, 임의의 정수들을 입력받고자 합니다! 몇 개의 임의의 정수들이 있는지 입력하세요!" << endl;
	cin >> n;
	w = new int[n + 1];			// 배열(포인터) w에 n+1의 크기만큼 동적 할당
	include = new int[n + 1];	// 배열(포인터) include에 n+1의 크기만큼 동적 할당
	cout << "지금부터 " << n << " 개의 정수들을 입력받겠습니다! 오름차순으로 입력해 주세요!" << endl;
	for (int i = 1; i <= n; i++)
	{
		cin >> w[i];
		total = total + w[i];
	}
	sum_of_subsets(0, 0, total);

	return 0;
}

// Algorithm 5.4 The Backtracking Algorithm for the Sum-of-Subsets Problem
// 문제 : n개 양의 정수(무게)와 양의 정수 W를 가지고, 합이 W가 되는 모든 정수의 조합을 모두 구하기
// 입력 : 양의 정수 n, (감소하지 않는 순으로) 정렬된 양의 정수의 배열 w(범위는 1부터 n), 양의 정수 W
// 출력 : 합이 W가 되는 모든 정수의 조합
// sum_of_subsets 최초 호출: sum_of_subsets(0, 0, total);
void sum_of_subsets(int i, int weight, int total)
{
	//cout << "i : " << i << endl;
	//cout << "weight : " << weight << endl;
	//cout << "total : " << total << endl;
	if (promising(i, weight, total))
	{
		if (weight == W)
		{
			cout << endl << "찾았다!" << endl;
			for (int p = 1; p <= i; p++)
			{
				cout << include[p] << " ";
			}
			cout << endl;
		}
		else {
			include[i + 1] = w[i + 1]; // 'yes' // w[i+1]을 포함한다.
			sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1]);
			include[i + 1] = 0;	// 'no' // w[i+1]을 포함하지 않는다.
			sum_of_subsets(i + 1, weight, total - w[i + 1]);
		}
	}
}

// 어떤 노드가 유망한지 아닌지를 판단하는 함수
bool promising(int i, int weight, int total)
{
	// cout << ((weight + total >= W) && (weight == W || weight + w[i + 1] <= W)) << endl;
	return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}
