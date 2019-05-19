// Coding by 남윤원, 20150413
// 쉬트라센의 행렬곱셈 알고리즘 구현 (구현언어 : C++)

#include <iostream>
#include <iomanip>
using namespace std;

// 기본적인 행렬 곱셈을 하는 표준 알고리즘 함수
void matrixmult(int n, int **A, int **B, int **C);

// 쉬트라센의 행렬 곱셈 알고리즘 함수
void strassen(int n, int **A, int **B, int **C);

int main()
{
	// 배열의 크기를 입력받아 보관함
	int n;

	cout << "배열의 크기 n을 입력하세요(단, 2의 거듭제곱이어야 합니다): ";
	cin >> n;
	cout << "생성되는 배열의 크기는 " << n << "*" << n << "입니다." << endl;

	// 입력받은 배열의 크기대로 세 배열을 동적 할당하여 생성
	// A, B는 n by n 행렬 입력을 받을 배열, C는 A * B 결과를 나타낼 배열
	int **A = new int*[n];
	for (int i = 0; i < n; i++)
		A[i] = new int[n];

	cout << "첫 번째 배열 안의 원소를 입력하세요\n";
	for (int i = 0; i < n; i++) {
		cout << i + 1 << "행의 원소를 입력하세요: ";
		for (int j = 0; j < n; j++)
			cin >> A[i][j];
	}

	// 확인용 코드
	/*
	for (int i = 0; i < n; i++) {
		cout << endl;
		for (int j = 0; j < n; j++)
			cout << A[i][j] << " " << endl;
	}
	*/

	int **B = new int*[n];
	for (int i = 0; i < n; i++)
		B[i] = new int[n];	

	cout << "두 번째 배열 안의 원소를 입력하세요\n";
	for (int i = 0; i < n; i++) {
		cout << i + 1 << "행의 원소를 입력하세요: ";
		for (int j = 0; j < n; j++)
			cin >> B[i][j];
	}

	int **C = new int*[n];
	for (int i = 0; i < n; i++)
		C[i] = new int[n];

	// int **A = { {1,2,3,4}, {5,6,7,8}, {9,1,2,3}, {4,5,6,7} };
	// int **B = { {8,9,1,2}, {3,4,5,6}, {7,8,9,1}, {2,3,4,5} };

 	strassen(n, A, B, C);
	// cout << "진짜 끝!!" << endl;

	cout << endl << "계산된 결과는 다음과 같습니다!" << endl << endl;

	cout.setf(ios::right);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << setw(5) << C[i][j] << " ";
		cout << endl;
	}

	cout << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << "C[" << i << "][" << j << "] = " << C[i][j] << endl;
		}
	}
	
	return 0;
}

// Algorithm 2.8 Strassen
// 문제 : n이 2의 거듭제곱일 때 2개의 n*n 행렬의 곱을 구하시오.
// 입력 : 2의 거듭제곱인 정수 n, 2개의 n*n 행렬 A와 B
// 출력 : A와 B의 곱 C
void strassen(int n, int **A, int **B, int **C)
{
	// cout << "strassen 실행 시작!!!" << endl;
	if (n <= 2) { 
		// 표준 알고리즘으로 C = A * B를 계산한다.
		matrixmult(n, A, B, C);
	}
	else {
		// A를 A_11, A_12, A_13, A_14로 분할한다.

		// int A11[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **A11 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			A11[i] = new int[n / 2];

		// int A12[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **A12 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			A12[i] = new int[n / 2];

		// int A21[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **A21 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			A21[i] = new int[n / 2];

		// int A22[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **A22 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			A22[i] = new int[n / 2];

		for (int i = 0; i < n / 2; i++) {
			for (int j = 0; j < n / 2; j++) {
				A11[i][j] = A[i][j];
				A12[i][j] = A[i][j + n / 2];
				A21[i][j] = A[i + n / 2][j];
				A22[i][j] = A[i + n / 2][j + n / 2];
			}
		}

		
		// 확인용 코드
		/*
			for (int i = 0; i < n/2; i++) {
				cout << endl;
				for (int j = 0; j < n/2; j++)
					cout << "A11[" << i << "][" << j << "] =" 
					<< A11[i][j] << " " << endl;
			}

			for (int i = 0; i < n / 2; i++) {
				cout << endl;
				for (int j = 0; j < n / 2; j++)
					cout << "A12[" << i << "][" << j << "] ="
					<< A12[i][j] << " " << endl;
			}

			for (int i = 0; i < n / 2; i++) {
				cout << endl;
				for (int j = 0; j < n / 2; j++)
					cout << "A21[" << i << "][" << j << "] ="
					<< A21[i][j] << " " << endl;
			}

			for (int i = 0; i < n / 2; i++) {
				cout << endl;
				for (int j = 0; j < n / 2; j++)
					cout << "A22[" << i << "][" << j << "] ="
					<< A22[i][j] << " " << endl;
			}
		*/

		// B를 B_11, B_12, B_13, B_14로 분할한다.
		// int B11[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **B11 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			B11[i] = new int[n / 2];

		// int B12[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **B12 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			B12[i] = new int[n / 2];

		// int B21[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **B21 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			B21[i] = new int[n / 2];

		// int B22[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **B22 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			B22[i] = new int[n / 2];

		for (int i = 0; i < n / 2; i++) {
			for (int j = 0; j < n / 2; j++) {
				B11[i][j] = B[i][j];
				B12[i][j] = B[i][j + n / 2];
				B21[i][j] = B[i + n / 2][j];
				B22[i][j] = B[i + n / 2][j + n / 2];
			}
		}
		// 확인용 코드
		/*
		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "B11[" << i << "][" << j << "] ="
				<< B11[i][j] << " " << endl;
		}

		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "B12[" << i << "][" << j << "] ="
				<< B12[i][j] << " " << endl;
		}

		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "B21[" << i << "][" << j << "] ="
				<< B21[i][j] << " " << endl;
		}

		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "B22[" << i << "][" << j << "] ="
				<< B22[i][j] << " " << endl;
		}
		*/

		// 쉬트라센의 방법으로 C = A*B를 계산하기
		// 1. M1부터 M7까지 구해 보자.

		// int temp1[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **temp1 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			temp1[i] = new int[n / 2];

		// int temp2[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **temp2 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			temp2[i] = new int[n / 2];

		// M1 = (A11 + A22) * (B11 + B22)

		// int M1[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **M1 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			M1[i] = new int[n / 2];

		for (int i = 0; i < n / 2; i++) {
			for (int j = 0; j < n / 2; j++) {
				temp1[i][j] = A11[i][j] + A22[i][j];
				temp2[i][j] = B11[i][j] + B22[i][j]; 
			}
		}
		
		/*
		//확인용 코드
		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "temp1[" << i << "][" << j << "] ="
				<< temp1[i][j] << " " << endl;
		}

		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "temp2[" << i << "][" << j << "] ="
				<< temp2[i][j] << " " << endl;
		}
		*/
		strassen(n / 2, temp1, temp2, M1);


		// M2 = (A21 + A22) * B11

		// int M2[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **M2 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			M2[i] = new int[n / 2];

		for (int i = 0; i < n / 2; i++) {
			for (int j = 0; j < n / 2; j++) {
				temp1[i][j] = A21[i][j] + A22[i][j];
			}
		}


		strassen(n / 2, temp1, B11, M2);

		/*
		// 확인
		cout << "m2" << endl;
		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "[" << i << "][" << j << "] ="
				<< M2[i][j] << " " << endl;
		}
		*/

		// M3 = A11 * (B12 - B22)

		// int M3[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **M3 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			M3[i] = new int[n / 2];

		for (int i = 0; i < n / 2; i++) {
			for (int j = 0; j < n / 2; j++) {
				temp1[i][j] = B12[i][j] - B22[i][j];
			}
		}
		strassen(n / 2, A11, temp1, M3);

		/*
		// 확인
		cout << "m3" << endl;
		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "temp1[" << i << "][" << j << "] ="
				<< M3[i][j] << " " << endl;
		}
		*/

		// M4 = A22 * (B21 - B11)

		// int M4[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **M4 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			M4[i] = new int[n / 2];

		for (int i = 0; i < n / 2; i++) {
			for (int j = 0; j < n / 2; j++) {
				temp1[i][j] = B21[i][j] - B11[i][j];
			}
		}



		strassen(n / 2, A22, temp1, M4);

		/*
		// 확인
		cout << "m4" << endl;
		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "temp1[" << i << "][" << j << "] ="
				<< M4[i][j] << " " << endl;
		}
		*/

		//M5 = (A11 + A12) * B22

		// int M5[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **M5 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			M5[i] = new int[n / 2];

		for (int i = 0; i < n / 2; i++) {
			for (int j = 0; j < n / 2; j++) {
				temp1[i][j] = A11[i][j] + A12[i][j];
			}
		}
		strassen(n / 2, temp1, B22, M5);

		/*
		// 확인
		cout << "m5" << endl;
		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "temp1[" << i << "][" << j << "] ="
				<< M5[i][j] << " " << endl;
		}
		*/

		// M6 = (A21 - A11) * (B11 + B12)

		// int M6[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **M6 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			M6[i] = new int[n / 2];

		for (int i = 0; i < n / 2; i++) {
			for (int j = 0; j < n / 2; j++) {
				temp1[i][j] = A21[i][j] - A11[i][j];
				temp2[i][j] = B11[i][j] + B12[i][j];
			}
		}
		strassen(n / 2, temp1, temp2, M6);

		/*
		// 확인
		cout << "m6" << endl;
		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "temp1[" << i << "][" << j << "] ="
				<< M6[i][j] << " " << endl;
		}
		*/

		// M7 = (A12 - A22) * (B21 + B22)

		// int M7[n / 2][n / 2]; 부분을 동적할당으로 구현
		int **M7 = new int*[n / 2];
		for (int i = 0; i < n / 2; i++)
			M7[i] = new int[n / 2];

		for (int i = 0; i < n / 2; i++) {
			for (int j = 0; j < n / 2; j++) {
				temp1[i][j] = A12[i][j] - A22[i][j];
				temp2[i][j] = B21[i][j] + B22[i][j];
			}
		}
		strassen(n / 2, temp1, temp2, M7);

		/*
		// 확인
		cout << "m7" << endl;
		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "temp1[" << i << "][" << j << "] ="
				<< M7[i][j] << " " << endl;
		}
		*/

	// 쉬트라쎈의 방법으로 C = A*B를 계산한다.
	// 2. 앞에서 구한 M1 ~ M7까지를 토대로 C11, C12, C21, C22를 구해서,
	//    전체 행렬 C의 각 위치에 집어넣어서 결과값 C를 완성한다.

	// C11 = M1 + M4 - M5 + M7
		for (int i = 0; i < n/2; i++) {
			for (int j = 0; j < n/2; j++) {
				C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
			}
		}
		

		// C12 = M3 + M5
		for (int i = 0; i < n/2; i++) {
			for (int j = 0; j < n/2; j++) {
				C[i][j + 2] = M3[i][j] + M5[i][j];
			}
		}


		// C21 = M2 + M4
		for (int i = 0; i < n/2; i++) {
			for (int j = 0; j < n/2; j++) {
				C[i + 2][j] = M2[i][j] + M4[i][j];
			}
		}

		// C22 = M1 + M3 - M2 + M6
		for (int i = 0; i < n/2; i++) {
			for (int j = 0; j < n/2; j++) {
				C[i + 2][j + 2] = M1[i][j] + M3[i][j] - M2[i][j] + M6[i][j];
			}
		}

		/*
		// 확인용 코드
		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "C11[" << i << "][" << j << "] ="
				<< C[i][j] << " " << endl;
		}

		// 확인용 코드
		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "C12[" << i << "][" << j << "] ="
				<< C[i][j + n / 2] << " " << endl;
		}

		// 확인용 코드
		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "C21[" << i << "][" << j << "] ="
				<< C[i + n / 2][j] << " " << endl;
		}

		// 확인용 코드
		for (int i = 0; i < n / 2; i++) {
			cout << endl;
			for (int j = 0; j < n / 2; j++)
				cout << "C22[" << i << "][" << j << "] ="
				<< C[i + n / 2][j + n / 2] << " " << endl;
		}
		*/

	}

	// cout << "strassen 끝!!!" << endl;
}

// 기본적인 행렬 곱셈을 하는 표준 알고리즘 함수
// 즉, 2*2 행렬을 표준 알고리즘으로 곱하는 함수, 따라서 n은 2 이하의 정수이어야 한다.
void matrixmult(int n, int **A, int **B, int **C)
{
	// cout << "matrixmult 시작!!" << endl;
	int i, j, k;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			C[i][j] = 0;
			for (k = 0; k < n; k++) {
				C[i][j] = C[i][j] + A[i][k] * B[k][j]; // 합을 누적
			}
		}
	}
	/*
	// 확인용 코드
		for (int i = 0; i < n; i++) {
			cout << endl;
			for (int j = 0; j < n; j++)
				cout << "C[" << i << "][" << j << "] ="
				<< C[i][j] << " " << endl;
		}
	*/
}