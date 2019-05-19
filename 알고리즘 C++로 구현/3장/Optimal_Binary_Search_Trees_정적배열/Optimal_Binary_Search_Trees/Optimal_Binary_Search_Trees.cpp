// coding by ������, 20150413
// Optimal Binary Search Trees

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Algorithm 3.9 Optimal Binary Search Tree(���� �̺а˻�Ʈ��)
void optsearchtree(int n, float *p, float& minavg, int **R);

// minimum �Լ� : Algorithm 3.9 Optimal Binary Search Tree(���� �̺а˻�Ʈ��) �� ȣ��Ǵ� �Լ�
float minimum(int i, int j, float **A, float *p, bool bo);

// sigma �Լ� : Algorithm 3.9 Optimal Binary Search Tree(���� �̺а˻�Ʈ��) �� ȣ��Ǵ� �Լ�
float sigma(int i, int j, float* p);

// main �Լ�
int main()
{
	float P[5] = { -1, (float)3/8, (float)3/8, (float)1/8, (float)1/8 };

	for(int i = 0; i < 5; i++)
		cout << P[i] << endl;

	float minavg = 0;

	int **R = new int*[6];
	for (int i = 0; i < 6; i++)
		R[i] = new int[6];

	cout << "optsearchtree ��!!" << endl;
		
	optsearchtree(5, P, minavg, R);

	cout << "minavg: " << minavg << endl;
	
	// Ȯ�ο� �ڵ�
	cout << endl << "R �迭 �� Ȯ��" << endl << endl;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++)
			cout << setw(10) << R[i][j] << " ";
		cout << endl << endl;
	}

}

// Algorithm 3.9 Optimal Binary Search Tree(���� �̺а˻�Ʈ��)
// ���� : �־��� ������ ������ ������ ���� �̺а˻�Ʈ���� �����Ѵ�.
//        ���⼭ �� ���ҿ� ���ؼ� �˻�Ű�� �� Ȯ���� �־�����.
// �Է� : n(������ ����), p(�ε����� ������ 1���� n������ �Ǽ� �迭), 
//        ���⼭ p[i]�� i��° ���Ҹ� ã�� Ȯ���̴�.
// ��� : ���� minarg(�� ���� ���� �̺а˻�Ʈ������ ��հ˻��ð�), ����Ʈ���� ������ �� �ִ� ������ �迭 R.
//        ���⼭ R�� ���� �ε��� ������ 1���� n+1�����̰�, ���� �ε��� ������ 0���� n�����̴�.
//        R[i][j]�� i°���� j°���� ���Ҹ� ������ ����Ʈ���� �Ѹ����� ������ �ε����̴�.
void optsearchtree(int n, float *p, float& minavg, int **R)
{ 
	cout << "optsearchtree ����!!" << endl;
	int i, j, k, diagonal;

	// ���� ������ A(2���� �迭)�� �����ϰ� ���� ũ�⸦ n+1�� �����Ҵ�
	// index�� pesudo code���� A[1...n+1][0...n]�̹Ƿ�, 
	// C++�� �����ÿ��� ���� n+1��ŭ �����Ҵ��Ͽ� �����Ѵ�.
	float **A = new float*[n + 1];
	for (int i = 0; i < n + 1; i++)
		A[i] = new float[n + 1];

	for (int i = 1; i <= n; i++) {
		A[i][i - 1] = 0;
		A[i][i] = p[i];
		R[i][i] = i;
		R[i][i - 1] = 0;
 	}
	
	cout << "adfa" << endl;

	//A[n + 1][n] = 0;
	//R[n + 1][n] = 0;

	// Ȯ�ο� �ڵ�
	cout << endl << "A �迭 �� Ȯ��" << endl << endl;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++)
			cout << setw(15) << A[i][j] << " ";
		cout << endl << endl;
	}

	// Ȯ�ο� �ڵ�
	cout << endl << "R �迭 �� Ȯ��" << endl << endl;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++)
			cout << setw(15) << R[i][j] << " ";
		cout << endl << endl;
	}

	for (diagonal = 1; diagonal <= n - 1; diagonal++) {
		for (i = 1; i <= n - diagonal; i++) { // diagonal - 1�� �� �밢�� ���� �ִ�.
			cout << "����for�� ���� ����!!" << endl;
			j = i + diagonal;
			if (j == 5) break;
			A[i][j] = minimum(i, j, A, p, true) + sigma(i, j, p);
			cout << minimum(i, j, A, p, true) + sigma(i, j, p) << endl;
			R[i][j] = minimum(i, j, A, p, false); // �ּҰ��� �ִ� k�� ��
		}
		minavg = A[1][n-1];
		cout << "�ּ� ��հ˻��ð��� " << minavg << endl;
	}

	// Ȯ�ο� �ڵ�
	cout << endl << "A �迭 �� Ȯ��" << endl << endl;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++)
			cout << setw(15) << A[i][j] << " ";
		cout << endl << endl;
	}


}


// minimum �Լ� : Algorithm 3.9 Optimal Binary Search Tree(���� �̺а˻�Ʈ��) �� ȣ��Ǵ� �Լ�
float minimum(int i, int j, float **A, float *p, bool bo)
{
	cout << "i�� ���� " << i << "�̰�, " << "j�� ���� " << j << "�Դϴ�!" << endl;
	int k = i;
	cout << "k�� ���� " << k << endl;
	int k_min = i;

	//Ȯ�ο� �ڵ�
	cout << "k_min�� ���� " << k << endl;
	cout << "A[i][k-1]�� ��: " << A[i][k-1] << endl;
	cout << "A[k+1][j]�� ��: " << A[k+1][j] << endl;
	
	float min = A[i][k - 1] + A[k + 1][j]; // �̶� min�� ����Ʈ���� ��հ˻��ð��̴�.
	cout << "min�� ����" << min << endl;
	for (; k < j; k++)
	{
		if (min > A[i][k] + A[k + 2][j])
		{
			cout << "min�� ����!" << endl;
			min = A[i][k] + A[k + 2][j];
			cout << "����� min���� " << min << endl;
			k_min = k + 1;
			cout << "����� k���� " << k << endl;
		}
	}
	if (bo == true) {
		cout << "bo�� ���̿���!" << endl;
		cout << "���� min�� ���� " << min << endl;
		return min;
	}
	else
	{
		cout << "bo�� �����̿���!" << endl;
		cout << "���� k�� ���� " << k_min << endl;
		return k_min;
	}
}

// sigma �Լ� : Algorithm 3.9 Optimal Binary Search Tree(���� �̺а˻�Ʈ��) �� ȣ��Ǵ� �Լ�
//             m = i ���� m = j ���� P_m�� ���� ���ϴ� ������ �Ѵ�.
float sigma(int i, int j, float* p)
{
	cout << "sigma �Լ� ����!!" << endl;
	float sum = 0;
	for (; i <= j; i++) {
		sum = sum + p[i];
	}
	cout << "sum = " << sum << endl;
	return sum;
}