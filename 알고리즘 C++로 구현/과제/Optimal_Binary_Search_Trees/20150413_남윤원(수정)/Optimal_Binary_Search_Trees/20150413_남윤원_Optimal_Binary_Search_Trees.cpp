// coding by 남윤원, 20150413
// Optimal Binary Search Trees

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Algorithm 3.9 Optimal Binary Search Tree(최적 이분검색트리)
void optsearchtree(int n, float *p, float& minavg, int **R);

// minimum 함수 : Algorithm 3.9 Optimal Binary Search Tree(최적 이분검색트리) 중 호출되는 함수
float minimum(int i, int j, float **A, float *p, bool bo);

// sigma 함수 : Algorithm 3.9 Optimal Binary Search Tree(최적 이분검색트리) 중 호출되는 함수
float sigma(int i, int j, float* p);

// main 함수
int main()
{
	int n;
	cout << "지금부터 Optimal Binary Search Tree의 최소 평균검색시간을 알아보겠습니다!" << endl;
	cout << "몇 개의 원소를 입력하실 건가요? ";
	cin >> n;
	n = n + 1;
	
	float *P = new float[n+1];
	
	cout << "지금부터는 각 원소의 확률을 입력받겠습니다!" << endl;
	cout << "각 원소의 확률을 입력하세요(단, 소수로 입력해야 합니다): " << endl;
	for (int i = 1; i < n; i++)
		cin >> P[i];
	/*
	// 확인용 코드
	for(int i = 0; i < n; i++)
		cout << P[i] << endl;
	*/
	float minavg = 0;

	int **R = new int*[n+1];
	for (int i = 0; i < n+1; i++)
		R[i] = new int[n+1];

	// cout << "optsearchtree 전!!" << endl;
		
	optsearchtree(n, P, minavg, R);

	cout << "minavg: " << minavg << endl;
	
	// 확인용 코드
	cout << endl << "R 배열 값 확인" << endl << endl;
	for (int i = 1; i < n+1; i++) {
		for (int j = 0; j < n; j++)
			cout << setw(15) << R[i][j] << " ";
		cout << endl << endl;
	}
	return 0;
}

// Algorithm 3.9 Optimal Binary Search Tree(최적 이분검색트리)
// 문제 : 주어진 원소의 집합을 가지고 최적 이분검색트리를 구축한다.
//        여기서 각 원소에 대해서 검색키가 될 확률이 주어진다.
// 입력 : n(원소의 개수), p(인덱스의 범위가 1부터 n까지인 실수 배열), 
//        여기서 p[i]는 i번째 원소를 찾을 확률이다.
// 출력 : 변수 minarg(이 값은 최적 이분검색트리에서 평균검색시간), 최적트리를 구축할 수 있는 이차원 배열 R.
//        여기서 R의 행의 인덱스 범위는 1부터 n+1까지이고, 열의 인덱스 범위는 0부터 n까지이다.
//        R[i][j]는 i째부터 j째까지 원소를 포함한 최적트리의 뿌리에서 원소의 인덱스이다.
void optsearchtree(int n, float *p, float& minavg, int **R)
{ 
	// cout << "optsearchtree 시작!!" << endl;
	int i, j, k, diagonal;

	// 이중 포인터 A(2차원 배열)을 선언하고 각각 크기를 n+1로 동적할당
	// index는 pesudo code에서 A[1...n+1][0...n]이므로, 
	// C++로 구현시에는 각각 n+1만큼 동적할당하여 구현한다.
	float **A = new float*[n + 1];
	for (int i = 0; i < n + 1; i++)
		A[i] = new float[n + 1];

	for (int i = 1; i <= n; i++) {
		A[i][i - 1] = 0;
		A[i][i] = p[i];
		R[i][i] = i;
		R[i][i - 1] = 0;
 	}
	
	//A[n + 1][n] = 0;
	//R[n + 1][n] = 0;
	/*
	// 확인용 코드
	cout << endl << "A 배열 값 확인" << endl << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < n; j++)
			cout << setw(15) << A[i][j] << " ";
		cout << endl << endl;
	}

	// 확인용 코드
	cout << endl << "R 배열 값 확인" << endl << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < n; j++)
			cout << setw(15) << R[i][j] << " ";
		cout << endl << endl;
	}
	*/
	for (diagonal = 1; diagonal <= n - 1; diagonal++) {
		for (i = 1; i <= n - diagonal; i++) { // diagonal - 1은 주 대각선 위에 있다.
			// cout << "이중for문 돌기 시작!!" << endl;
			j = i + diagonal;
			if (j == n) break; // 이 break문이 없을 경우 error가 난다. 
							   // C++에서의 배열과 행렬의 index의 차이가 있기 때문에 그렇다.
			cout << "j의 값은: " << j << endl;
			cout << "n의 값은: " << n << endl;
			A[i][j] = minimum(i, j, A, p, true) + sigma(i, j, p); // 최적트리의 평균검색시간
			// cout << minimum(i, j, A, p, true) + sigma(i, j, p) << endl;
			R[i][j] = minimum(i, j, A, p, false); // 최소값을 주는 k의 값
		}
		minavg = A[1][n-1];
	}

	// 확인용 코드
	cout << endl << "A 배열 값 확인" << endl << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < n; j++)
			cout << setw(15) << A[i][j] << " ";
		cout << endl << endl;
	}
}


// minimum 함수 : Algorithm 3.9 Optimal Binary Search Tree(최적 이분검색트리) 중 호출되는 함수
float minimum(int i, int j, float **A, float *p, bool bo)
{
	//cout << "i의 값은 " << i << "이고, " << "j의 값은 " << j << "입니다!" << endl;
	int k = i;
	//cout << "k의 값은 " << k << endl;
	int k_min = i;
	/*
	//확인용 코드
	cout << "k_min의 값은 " << k << endl;
	cout << "A[i][k-1]의 값: " << A[i][k-1] << endl;
	cout << "A[k+1][j]의 값: " << A[k+1][j] << endl;
	*/
	float min = A[i][k - 1] + A[k + 1][j]; // 이때 min은 최적트리의 평균검색시간이다.
	//cout << "min의 값은" << min << endl;
	for (; k < j; k++)
	{
		if (min > A[i][k] + A[k + 2][j])
		{
			//cout << "min값 변경!" << endl;
			min = A[i][k] + A[k + 2][j];
			//cout << "변경된 min값은 " << min << endl;
			k_min = k + 1;
			//cout << "변경된 k값은 " << k << endl;
		}
	}
	if (bo == true) {
		//cout << "bo는 참이예요!" << endl;
		//cout << "최종 min의 값은 " << min << endl;
		return min;
	}
	else
	{
		//cout << "bo는 거짓이예요!" << endl;
		//cout << "최종 k의 값은 " << k_min << endl;
		return k_min;
	}
}

// sigma 함수 : Algorithm 3.9 Optimal Binary Search Tree(최적 이분검색트리) 중 호출되는 함수
//             m = i 부터 m = j 까지 P_m의 값을 더하는 역할을 한다.
float sigma(int i, int j, float* p)
{
	// cout << "sigma 함수 시작!!" << endl;
	float sum = 0; // 0으로 초기화
	for (; i <= j; i++) {
		sum = sum + p[i];
	}
	//cout << "sum = " << sum << endl;
	return sum;
}