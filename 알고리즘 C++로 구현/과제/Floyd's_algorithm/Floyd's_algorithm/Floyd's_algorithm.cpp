// Coding by ������, 20150413
// Floyd's algorithm ���� (������� : C++)

#include <iostream>
#include <iomanip>
using namespace std;

// P�� ����(global) �迭�� �����Ѵ�.
// unsigned int �迭�� ������ ������, P�� -10000���� �Է��� �� ����÷ο츦 �����Ͽ�
// �ִ��� ����Ǿ� ���Ѵ��� ���� ǥ���ϱ� �����ϱ� �����̴�.
// P�� -1�� �Է��ؼ� unsigned int�� �ִ��� ������ ���
// ������ D[i][k] + D[k][j]�� ���� �� �����÷ο찡 �߻��� �� �����Ƿ�,
// P�� -10000�� �Է��Ͽ� �� ���ɼ��� ���̵��� �����Ѵ�.
unsigned int **P;

// Algorithm 3.4 floyd2
void floyd2(int n, unsigned int **W, unsigned int **D, unsigned int **P);

// Algorithm 3.5 path
void path(int q, int r);

int main()
{
	int Vertex;
	cout << "���ݺ��� Floyd�� �˰������� �ִܰ�θ� �˾ƺ��ڽ��ϴ�!" << endl;
	cout << "�� ���� ����(Vertex)�� �ֳ���? ";
	cin >> Vertex;
	cout << "Vertex�� " << Vertex << "���� �����Ǿ����ϴ�!" << endl;

	// �Է¹��� Vertex�� ũ���� �����͸� �Է¹��� 2���� �迭(���� ������) W�� ���� �Ҵ��Ѵ�.
	unsigned int **W = new unsigned int*[Vertex];
	for (int i = 0; i < Vertex; i++)
		W[i] = new unsigned int[Vertex];

	cout << "������(edge)�� ����ġ(weight)�� �Է��� �ּ���!" << endl;
	cout << "����ġ(weight)�� ���Ѵ��� ��� -10000�Դϴ�." << endl;
	cout << "�ڱ� �ڽ��� ����ġ(weight)�� 0���� �մϴ�." << endl;

	for (int i = 0; i < Vertex; i++) {
		cout << "V" << i + 1 << "���� �� edge�� ���� weight : ";
		for (int j = 0; j < Vertex; j++)
			cin >> W[i][j];
	}

	// Ȯ�ο� �ڵ�
	cout << endl << "W �迭 �� Ȯ��" << endl << endl;
	for (int i = 0; i < Vertex; i++) {
		for (int j = 0; j < Vertex; j++)
			cout << setw(10) << W[i][j] << " ";
		cout << endl << endl;
	}

	// �ִ� ����� ���̸� ��Ÿ�� 2���� �迭(���� ������) D�� ���� �Ҵ��Ѵ�.
	unsigned int **D = new unsigned int*[Vertex];
	for (int i = 0; i < Vertex; i++)
		D[i] = new unsigned int[Vertex];

	// �ִ� ��θ� ��Ÿ�� ���� 2���� �迭(���� ������) P�� ���� �Ҵ��Ѵ�.
	P = new unsigned int*[Vertex];
	for (int i = 0; i < Vertex; i++)
		P[i] = new unsigned int[Vertex];

	floyd2(Vertex, W, D, P);
	path(4, 1);
	cout << endl;
	return 0;
}

// Algorithm 3.4 floyd2
// ���� : ����ġ���� �׷����� �� ���𿡼� �ٸ� ��� ����� ���� �ִܰ�θ� ��� �����
//        ���⿡ ���ؼ� �ִܰ�ε� ã��
// �Է� : ���� ������ n�� ����ġ���� ����׷���, �׷����� 2���� �迭 W�� ǥ���ϴµ�, 
//        ��� ���� �ε��� ������ 1���� n�����̴�.
//        ��, W[i][j]�� ���� i���� ���� j�� ���� �������� ����ġ�̴�.
// ��� : ��� ���� �ε��� ������ 1���� n������ 2���� �迭 D.
//        ��, D[i][j]�� ���� i���� ���� j�� ���� �ִܰ���� ���̰� �ȴ�.
//        ���⿡, ��� ���� �ε��� ������ ��� 1���� n������ �迭 P ���� ����̴�.
void floyd2(int n, unsigned int **W, unsigned int **D, unsigned int **P)
{
	// cout << "floyd2 ����!!" << endl;

	int i, j, k;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			P[i][j] = 0;
	
	// cout << "D�� W�� ���ٴ°� ������ �ſ���!" << endl;
	D = W;
	// cout << "D�� W�� ���ƿ�!" << endl;
	/*
	cout << "D �迭 �� Ȯ��" << endl << endl;

	// Ȯ�ο� �ڵ�
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
					// �迭�� index�� 0���� �����ϴµ�, ���� index = 0�� ���,
					// �ִܰ���� �߰��� �����ִ� ������ ���� ��쵵 0�̹Ƿ� ������ ������ �ִ�.
					// �̸� �����ϱ� ���� �ϴ� k���� 1�� ���� ���� P[i][j]�� �־��ش�.
					P[i][j] = k+1;	
					D[i][j] = D[i][k] + D[k][j];
				}

	cout << "D �迭 �� Ȯ��" << endl << endl;

	// Ȯ�ο� �ڵ�
	for (int i = 0; i < n; i++)	{
		for (int j = 0; j < n; j++)
			cout << setw(10) << D[i][j] << " ";
		cout << endl;
		cout << endl;
	}

	cout << "P �迭 �� Ȯ��" << endl << endl;

	// Ȯ�ο� �ڵ�
	for (int i = 0; i < n; i++)	{
		for (int j = 0; j < n; j++)
			cout << setw(10) << P[i][j] << " ";
		cout << endl;
		cout << endl;
	}

	// cout << "floyd2 �Ϸ�!!" << endl << endl;
}


// Algorithm 3.5 path
// ���� : ����ġ���� �׷������� �� ���𿡼� �ٸ� ����� ���� �ִܰ�� �� �ִ�
//        �߰� ������� ����Ͻÿ�.
// �Է� : �˰��� 3.4�� ���� �迭 P�� �˰��� 3.4�� �Է��� �׷��� ������ �ε��� q�� r
// ��� ȣ���� �� ���� ���ϴ� ������ ��� �Լ��� �Է� �Ķ���ͷ� �ϱ�� ����.
// �׷��Ƿ�, P�� ����(global) �迭�� �����Ѵ�.
void path(int q, int r)
{
	// �Ʊ� k���� 1�� ����Ǿ� �־����Ƿ� �ٽ� 1�� ���־�� �Ѵ�.
	// ���� ���, path(5,3)�� �ԷµǾ��� ���
	// �迭 �󿡼��� P[5-1][3-1] �� P[4][2]�� �ִ� ���� Ȯ���ؾ� �Ѵ�.
	if (P[q-1][r-1] != 0) {
		path(q, P[q-1][r-1]);
		cout << "v" << P[q-1][r-1] << "    ";
		path(P[q-1][r-1], r);
	}
}