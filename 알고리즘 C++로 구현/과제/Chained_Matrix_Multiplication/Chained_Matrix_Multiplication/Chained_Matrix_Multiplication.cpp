// coding by 남윤원, 20150413
// Algorithm 3.6 Minimum Multiplications (최소 곱셈)
// Algorithm 3.7 Print Optimal Order(최적의 순서 출력)를 교재 pesudo code에 충실하게 구현

#include <iostream>
#include <iomanip>
using namespace std;

int **P; // 전역배열로 선언

int** minmult(int n, int *d); // Algorithm 3.6 Minimum Multiplications 함수

int minimum(int i, int j, int **M, int *d, bool bo = true); // minimum 함수

void order(int i, int j); // Algorithm 3.7 Print Optimal Order 함수

int main()
{
	int n;
	cout << "지금부터 행렬을 곱하는 최적의 순서를 알아봅시다!" << endl;
	cout << "몇 개의 행렬을 곱하실 건가요? ";
	cin >> n;
	cout << endl << n << "개의 행렬을 곱하는 최적의 순서를 알아보겠습니다!" << endl;
	
	int *d = new int[n+1]; // 1차원 배열(=포인터) d를 선언 후 n+1만큼 동적 할당 (0 ~ n만큼 필요)
	
	cout << "지금부터는 각 행렬의 행과 열 수를 입력받겠습니다!" << endl;
	cout << "단, 행렬의 곱셈을 위해서는 n번째 행렬의 열 수와 n+1번째 행렬의 행 수가 동일해야 합니다." << endl;
	cout << "따라서, 각 행렬의 열 수만을 입력받되, 첫 번째 행렬의 경우 행 수까지 입력받도록 하겠습니다." << endl;
	for (int i = 0; i < n+1; i++) {
		if (i == 0) {	                                // 첫 번쨰 행렬이면
			cout << i + 1 << "번째 행렬의 행 개수 : ";	
			cin >> d[i];								// 첫 번째 행렬의 행 수를 입력받아서, d[0]에 저장
			cout << i + 1 << "번째 행렬의 열 개수 : ";
			i++;										// i의 값 1 증가
			cin >> d[i];								// 첫 번째 행렬의 열 수를 입력받아서, d[0]에 저장
		}
		else
		{
			cout << i + 1 << "번째 행렬의 열 개수 : ";
			cin >> d[i];								// i 번째 행렬의 열 수를 입력받아서, d[i]에 저장
		}
	}

	/*
	// d 행렬 확인
	cout << "d행렬 확인" << endl;
	for (int i = 0; i < n+1; i++)
	{
		cout << "d[" << i << "] = " << d[i] << endl;
	}
	*/

	// Mfinal 2차원 배열(=이중 포인터)에 n+1의 크기만큼 동적할당
	int **Mfinal = new int*[n+1];
	for (int i = 0; i < n+1; i++)
		Mfinal[i] = new int[n+1];

	// 전역 배열로 선언한 P에 n+1의 크기만큼 동적할당
	P = new int*[n + 1];
	for (int i = 0; i < n + 1; i++)
		P[i] = new int[n + 1];

	// Algorithm 3.6 Minimum Multiplications (최소 곱셈)
	// minmult 함수 실행!
	Mfinal = minmult(n, d);

	// 확인용 코드
	cout << endl << "M 배열 값 확인" << endl << endl;
	for (int i = 0; i < n+1; i++) {
		for (int j = 0; j < n+1; j++)
			cout << setw(10) << Mfinal[i][j] << " ";
		cout << endl << endl;
	}

	// 확인용 코드
	cout << endl << "P 배열 값 확인" << endl << endl;
	for (int i = 0; i < n+1; i++) {
		for (int j = 0; j < n+1; j++)
			cout << setw(10) << P[i][j] << " ";
		cout << endl << endl;
	}

	// Algorithm 3.7 Print Optimal Order(최적의 순서 출력)
	// order 함수 실행!
	order(1, n);

	return 0;
}

// Algorithm 3.6 Minimum Multiplications (최소 곱셈)
// 문제 : 행렬 n개를 곱하는데 필요한 원소단위 곱셈의 최소 횟수와 
//        최소 횟수로 행렬 곱셈을 하는 순서를 구하시오.
// 입력 : n(행렬의 개수), 인덱스의 범위가 0부터 n까지인 정수 배열 d, 여기서 d[i-1]*d[i]는
//	      i번째 행렬의 크기가 된다.
// 출력 : minmult(n개 행렬을 곱하는데 필요한 원소단위 곱셈의 최소 횟수)
//        P(최적의 순서를 구할 수 있는 이차원 배열)
//       여기서 P의 행의 인덱스는 1부터 n-1까지이고, 열의 인덱스는 1부터 n까지이다.
//       P[i][j]의 값은 i부터 j까지 행렬을 곱할 떄 최적의 순서로 갈라지는 기점을 나타낸다.
int** minmult(int n, int *d) // P는 전역배열로 선언
{
	int i, j, k, diagonal;

	// 0부터 n까지의 동적 배열 생성, 실제 사용은 1부터 n까지만 사용할 예정
	int **M = new int*[n+1];
	for (int i = 0; i < n+1; i++)
		M[i] = new int[n+1];
	
	// 1부터 n까지 i의 범위에 넣고, M[i][i]의 값을 0으로 만든다.
	for (i = 1; i < n+1; i++)
		M[i][i] = 0;

	/*
	// 확인용 코드
	cout << endl << "M 배열 값 확인" << endl << endl;
	for (i = 1; i < n+1; i++) {
		cout << M[i][i] << endl;
	}
	*/

	for (diagonal = 1; diagonal <= n - 1; diagonal++)  // diagonal-1은 주 대각선의
		for (i = 1; i <= n - diagonal; i++) {		   // 바로 위에 있는
			// cout << i << "번째 시작!" << endl;
			j = i + diagonal;						   // 대각선을 의미한다.
			M[i][j] = minimum(i, j, M, d, true);       // i <= k <= j-1
			P[i][j] = minimum(i, j, M, d, false);      // 최소 횟수를 나타내는 k의 값
			// cout << i << "번째 종료!" << endl;
		}

	return M;
}


// minimum 함수 : Algorithm 3.6 Minimum Multiplications (최소 곱셈) 중 호출되는 함수
int minimum(int i, int j, int **M, int *d, bool bo)
{
	// cout << "i의 값은 " << i << "이고, " << "j의 값은 " << j << "입니다!" << endl;
	int k = i;
	// cout << "k의 값은 " << k << endl;
	int k_min = i;

	/* 확인용 코드
	cout << "k_min의 값은 " << k << endl;
	cout << "M[i][k]의 값: " << M[i][k] << endl;
	cout << "M[k+1][j]의 값: " << M[k+1][j] << endl;
	cout << "d[i]d[k]d[j]의 값: " << d[i - 1] * d[k] * d[j] << endl;
	*/

	int min = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
	// cout << "min의 값은" << min << endl;
	for (; k < j - 1; k++)
	{
		if (min > M[i][k + 1] + M[k + 2][j] + d[i - 1] * d[k + 1] * d[j])
		{
			// cout << "min값 변경!" << endl;
			min = M[i][k + 1] + M[k + 2][j] + d[i - 1] * d[k + 1] * d[j];
			// cout << "변경된 min값은 " << min << endl;
			k_min = k+1;
			// cout << "변경된 k값은 " << k << endl;
		}
	}
	if (bo == true) {
		// cout << "bo는 참이예요!" << endl;
		// cout << "최종 min의 값은 " << min << endl;
		return min;
	}
	else
	{
		// cout << "bo는 거짓이예요!" << endl;
		// cout << "최종 k의 값은 " << k_min << endl;
		return k_min;
	}
}

// Algorithm 3.7 Print Optimal Order (최적의 순서 출력)
// 문제 : n개 행렬을 곱하는 최적의 순서를 출력하시오.
// 입력 : n(양의 정수), P(알고리즘 3.6에서 만든 배열).
// 여기서 P[i][j]의 값은 i부터 j까지 행렬을 곱할 때 최적의 순서로 갈라지는 기점을 나타냄
// 출력 : 행렬을 곱하는 최적의 순서
void order(int i, int j)
{
	if (i == j)
		cout << "A" << i;
	else {
		int k;
		k = P[i][j];
		cout << "(";
		order(i, k);
		order(k + 1, j);
		cout << ")";
	}
}