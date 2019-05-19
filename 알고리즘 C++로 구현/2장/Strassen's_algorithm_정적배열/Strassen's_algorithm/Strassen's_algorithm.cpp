#include <iostream>
using namespace std;

void matrixmult(int n, int A[2][2], int B[2][2], int C[2][2]);
void strassen(int n, int A[4][4], int B[4][4], int C[4][4]);

int A[4][4] = { {1,2,3,4}, {5,6,7,8}, {9,1,2,3}, {4,5,6,7} };
int B[4][4] = { {8,9,1,2}, {3,4,5,6}, {7,8,9,1}, {2,3,4,5} };

int A11[2][2] = { {0,0}, {0,0} };
int A12[2][2] = { {0,0}, {0,0} };
int A21[2][2] = { {0,0}, {0,0} };
int A22[2][2] = { {0,0}, {0,0} };
int B11[2][2] = { {0,0}, {0,0} };
int B12[2][2] = { {0,0}, {0,0} };
int B21[2][2] = { {0,0}, {0,0} };
int B22[2][2] = { {0,0}, {0,0} };

int M1[2][2] = { {0,0}, {0,0} };
int M2[2][2] = { {0,0}, {0,0} };
int M3[2][2] = { {0,0}, {0,0} };
int M4[2][2] = { {0,0}, {0,0} };
int M5[2][2] = { {0,0}, {0,0} };
int M6[2][2] = { {0,0}, {0,0} };
int M7[2][2] = { {0,0}, {0,0} };


int main()
{
	int n = 4;
	int C[4][4];

	strassen(4, A, B, C);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << "C[" << i << "][" << j << "] = " << C[i][j] << endl;
		}
	}

	return 0;
}

void strassen(int n, int A[4][4], int B[4][4], int C[4][4])
{
	if (n <= 2) {
		// 표준 알고리즘으로 C = A * B를 계산한다.
		// matrixmult(...);
	}
	else {
		// A를 A_11, A_12, A_13, A_14로 분할한다.
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				A11[i][j] = A[i][j];
			}
		}

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				A12[i][j] = A[i][j + 2];
			}
		}

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				A21[i][j] = A[i + 2][j];
			}
		}

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				A22[i][j] = A[i + 2][j + 2];
			}
		}

		// B를 B_11, B_12, B_13, B_14로 분할한다.
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				B11[i][j] = B[i][j];
			}
		}

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				B12[i][j] = B[i][j + 2];
			}
		}

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				B21[i][j] = B[i + 2][j];
			}
		}

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				B22[i][j] = A[i + 2][j + 2];
			}
		}

		// M1 = (A11 + A22) * (B11 + B22)
		int temp1[2][2];
		int temp2[2][2];

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				temp1[i][j] = A11[i][j] + A22[i][j];
				temp2[i][j] = B11[i][j] + B22[i][j];
			}
		}
		matrixmult(2, temp1, temp2, M1);


		// M2 = (A21 + A22) * B11
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				temp1[i][j] = A21[i][j] + A22[i][j];
			}
		}
		matrixmult(2, temp1, B11, M2);
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)

				// M3 = A11 * (B12 - B22)
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 2; j++) {
						temp1[i][j] = B12[i][j] - B22[i][j];
					}
				}
		matrixmult(2, A11, temp1, M3);

		// M4 = A22 * (B21 - B11)
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				temp1[i][j] = B21[i][j] - B11[i][j];
			}
		}
		matrixmult(2, A22, temp1, M4);

		// M5 = (A11 + A12) * B22
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				temp1[i][j] = A11[i][j] - A12[i][j];
			}
		}
		matrixmult(2, temp1, B22, M5);

		// M6 = (A21 - A11) * (B11 + B12)
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				temp1[i][j] = A21[i][j] - A11[i][j];
				temp2[i][j] = B11[i][j] + B12[i][j];
			}
		}
		matrixmult(2, temp1, temp2, M6);

		// M7 = (A12 - A22) * (B21 + B22)
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				temp1[i][j] = A12[i][j] - A22[i][j];
				temp2[i][j] = B21[i][j] + B22[i][j];
			}
		}
		matrixmult(2, temp1, temp2, M7);
	}

	// 쉬트라쎈의 방법으로 C = A*B를 계산한다.

	// C11 = M1 + M4 - M5 + M7
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
		}
	}

	// C12 = M3 + M5
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			C[i][j + 2] = M3[i][j] + M5[i][j];
		}
	}

	// C21 = M2 + M4
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			C[i + 2][j] = M2[i][j] + M4[i][j];
		}
	}

	// C22 = M1 + M3 - M2 + M6
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			C[i + 2][j + 2] = M1[i][j] + M3[i][j] - M2[i][j] + M6[i][j];
		}
	}
}

void matrixmult(int n, int A[2][2], int B[2][2], int C[2][2])
{
	int i, j, k;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			C[i][j] = 0;
			for (k = 0; k < n; k++) {
				C[i][j] = C[i][j] + A[i][k] * B[k][j]; // 합을 누적
			}
		}
	}
}