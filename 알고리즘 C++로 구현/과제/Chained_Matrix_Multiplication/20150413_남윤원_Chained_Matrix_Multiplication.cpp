// coding by ������, 20150413
// Algorithm 3.6 Minimum Multiplications (�ּ� ����)
// Algorithm 3.7 Print Optimal Order(������ ���� ���)�� ���� pesudo code�� ����ϰ� ����

#include <iostream>
#include <iomanip>
using namespace std;

int **P; // �����迭�� ����

int** minmult(int n, int *d); // Algorithm 3.6 Minimum Multiplications �Լ�

int minimum(int i, int j, int **M, int *d, bool bo = true); // minimum �Լ�

void order(int i, int j); // Algorithm 3.7 Print Optimal Order �Լ�

int main()
{
	int n;
	cout << "���ݺ��� ����� ���ϴ� ������ ������ �˾ƺ��ô�!" << endl;
	cout << "�� ���� ����� ���Ͻ� �ǰ���? ";
	cin >> n;
	cout << endl << n << "���� ����� ���ϴ� ������ ������ �˾ƺ��ڽ��ϴ�!" << endl;
	
	int *d = new int[n+1]; // 1���� �迭(=������) d�� ���� �� n+1��ŭ ���� �Ҵ� (0 ~ n��ŭ �ʿ�)
	
	cout << "���ݺ��ʹ� �� ����� ��� �� ���� �Է¹ްڽ��ϴ�!" << endl;
	cout << "��, ����� ������ ���ؼ��� n��° ����� �� ���� n+1��° ����� �� ���� �����ؾ� �մϴ�." << endl;
	cout << "����, �� ����� �� ������ �Է¹޵�, ù ��° ����� ��� �� ������ �Է¹޵��� �ϰڽ��ϴ�." << endl;
	for (int i = 0; i < n+1; i++) {
		if (i == 0) {	                                // ù ���� ����̸�
			cout << i + 1 << "��° ����� �� ���� : ";	
			cin >> d[i];								// ù ��° ����� �� ���� �Է¹޾Ƽ�, d[0]�� ����
			cout << i + 1 << "��° ����� �� ���� : ";
			i++;										// i�� �� 1 ����
			cin >> d[i];								// ù ��° ����� �� ���� �Է¹޾Ƽ�, d[0]�� ����
		}
		else
		{
			cout << i + 1 << "��° ����� �� ���� : ";
			cin >> d[i];								// i ��° ����� �� ���� �Է¹޾Ƽ�, d[i]�� ����
		}
	}

	/*
	// d ��� Ȯ��
	cout << "d��� Ȯ��" << endl;
	for (int i = 0; i < n+1; i++)
	{
		cout << "d[" << i << "] = " << d[i] << endl;
	}
	*/

	// Mfinal 2���� �迭(=���� ������)�� n+1�� ũ�⸸ŭ �����Ҵ�
	int **Mfinal = new int*[n+1];
	for (int i = 0; i < n+1; i++)
		Mfinal[i] = new int[n+1];

	// ���� �迭�� ������ P�� n+1�� ũ�⸸ŭ �����Ҵ�
	P = new int*[n + 1];
	for (int i = 0; i < n + 1; i++)
		P[i] = new int[n + 1];

	// Algorithm 3.6 Minimum Multiplications (�ּ� ����)
	// minmult �Լ� ����!
	Mfinal = minmult(n, d);

	// Ȯ�ο� �ڵ�
	cout << endl << "M �迭 �� Ȯ��" << endl << endl;
	for (int i = 0; i < n+1; i++) {
		for (int j = 0; j < n+1; j++)
			cout << setw(10) << Mfinal[i][j] << " ";
		cout << endl << endl;
	}

	// Ȯ�ο� �ڵ�
	cout << endl << "P �迭 �� Ȯ��" << endl << endl;
	for (int i = 0; i < n+1; i++) {
		for (int j = 0; j < n+1; j++)
			cout << setw(10) << P[i][j] << " ";
		cout << endl << endl;
	}

	// Algorithm 3.7 Print Optimal Order(������ ���� ���)
	// order �Լ� ����!
	order(1, n);

	return 0;
}

// Algorithm 3.6 Minimum Multiplications (�ּ� ����)
// ���� : ��� n���� ���ϴµ� �ʿ��� ���Ҵ��� ������ �ּ� Ƚ���� 
//        �ּ� Ƚ���� ��� ������ �ϴ� ������ ���Ͻÿ�.
// �Է� : n(����� ����), �ε����� ������ 0���� n������ ���� �迭 d, ���⼭ d[i-1]*d[i]��
//	      i��° ����� ũ�Ⱑ �ȴ�.
// ��� : minmult(n�� ����� ���ϴµ� �ʿ��� ���Ҵ��� ������ �ּ� Ƚ��)
//        P(������ ������ ���� �� �ִ� ������ �迭)
//       ���⼭ P�� ���� �ε����� 1���� n-1�����̰�, ���� �ε����� 1���� n�����̴�.
//       P[i][j]�� ���� i���� j���� ����� ���� �� ������ ������ �������� ������ ��Ÿ����.
int** minmult(int n, int *d) // P�� �����迭�� ����
{
	int i, j, k, diagonal;

	// 0���� n������ ���� �迭 ����, ���� ����� 1���� n������ ����� ����
	int **M = new int*[n+1];
	for (int i = 0; i < n+1; i++)
		M[i] = new int[n+1];
	
	// 1���� n���� i�� ������ �ְ�, M[i][i]�� ���� 0���� �����.
	for (i = 1; i < n+1; i++)
		M[i][i] = 0;

	/*
	// Ȯ�ο� �ڵ�
	cout << endl << "M �迭 �� Ȯ��" << endl << endl;
	for (i = 1; i < n+1; i++) {
		cout << M[i][i] << endl;
	}
	*/

	for (diagonal = 1; diagonal <= n - 1; diagonal++)  // diagonal-1�� �� �밢����
		for (i = 1; i <= n - diagonal; i++) {		   // �ٷ� ���� �ִ�
			// cout << i << "��° ����!" << endl;
			j = i + diagonal;						   // �밢���� �ǹ��Ѵ�.
			M[i][j] = minimum(i, j, M, d, true);       // i <= k <= j-1
			P[i][j] = minimum(i, j, M, d, false);      // �ּ� Ƚ���� ��Ÿ���� k�� ��
			// cout << i << "��° ����!" << endl;
		}

	return M;
}


// minimum �Լ� : Algorithm 3.6 Minimum Multiplications (�ּ� ����) �� ȣ��Ǵ� �Լ�
int minimum(int i, int j, int **M, int *d, bool bo)
{
	// cout << "i�� ���� " << i << "�̰�, " << "j�� ���� " << j << "�Դϴ�!" << endl;
	int k = i;
	// cout << "k�� ���� " << k << endl;
	int k_min = i;

	/* Ȯ�ο� �ڵ�
	cout << "k_min�� ���� " << k << endl;
	cout << "M[i][k]�� ��: " << M[i][k] << endl;
	cout << "M[k+1][j]�� ��: " << M[k+1][j] << endl;
	cout << "d[i]d[k]d[j]�� ��: " << d[i - 1] * d[k] * d[j] << endl;
	*/

	int min = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
	// cout << "min�� ����" << min << endl;
	for (; k < j - 1; k++)
	{
		if (min > M[i][k + 1] + M[k + 2][j] + d[i - 1] * d[k + 1] * d[j])
		{
			// cout << "min�� ����!" << endl;
			min = M[i][k + 1] + M[k + 2][j] + d[i - 1] * d[k + 1] * d[j];
			// cout << "����� min���� " << min << endl;
			k_min = k+1;
			// cout << "����� k���� " << k << endl;
		}
	}
	if (bo == true) {
		// cout << "bo�� ���̿���!" << endl;
		// cout << "���� min�� ���� " << min << endl;
		return min;
	}
	else
	{
		// cout << "bo�� �����̿���!" << endl;
		// cout << "���� k�� ���� " << k_min << endl;
		return k_min;
	}
}

// Algorithm 3.7 Print Optimal Order (������ ���� ���)
// ���� : n�� ����� ���ϴ� ������ ������ ����Ͻÿ�.
// �Է� : n(���� ����), P(�˰��� 3.6���� ���� �迭).
// ���⼭ P[i][j]�� ���� i���� j���� ����� ���� �� ������ ������ �������� ������ ��Ÿ��
// ��� : ����� ���ϴ� ������ ����
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