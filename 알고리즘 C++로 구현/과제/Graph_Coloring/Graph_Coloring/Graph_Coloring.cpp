// coding by 20150413 ������
// Graph Coloring

#include <iostream>
#include <iomanip>
using namespace std;

int n;	     // ������ ����
int m;       // ���� ����
int *vcolor; // ������� ������ �迭(������)
int **W;	 // �Է¹��� ����� �׷���

void m_coloring(int i);
bool promising(int i);

int main()
{
	// ����ڷκ��� ����� �׷����� �Է¹޴´�.	
	cout << "���ݺ��� �׷��� ��ĥ�ϱ� ������ Ǯ�� ���ڽ��ϴ�!" << endl;
	cout << "����� �׷����� �Է��� �ּ���!" << endl;

	cout << "�� ���� ������ �ֳ���? ";
	cin >> n;
	cout << "������ " << n << "���� �����Ǿ����ϴ�!" << endl;

	// �Է¹��� ������ ����(n)��� ������� ������ �迭(������) vcolor�� ���� �Ҵ��Ѵ�.
	vcolor = new int[n + 1];

	// �Է¹��� ������ ����(n)��� �����͸� �Է¹��� 2���� �迭(���� ������) W�� ���� �Ҵ��Ѵ�.
	W = new int*[n+1];
	for (int i = 1; i <= n; i++)
		W[i] = new int[n+1];

	cout << "������(edge)�� ���� ������ �ִ����� ���θ� �Է��� �ּ���!" << endl;
	cout << "������ ������ 1, ������ ���� ������ 0�Դϴ�."  << endl;
	cout << "�ڱ� �ڽ��� ������ ���� �ʴٰ� �����ϰ�, 0���� �Է��Ͽ� �ּ���." << endl;

	for (int i = 1; i <= n; i++) {
		cout << "V" << i << "���� �� edge�� ������ �ִ��� ���� : ";
		for (int j = 1; j <= n; j++)
		{
			cin >> W[i][j];
		}
	}

	// ����ڷκ��� ������ �Է¹޴´�.
	cout << "�� ���� ����� �׷����� ĥ�Ͻ� �ǰ���? ";
	cin >> m;
	cout << m << "���� ����� ĥ�� ���ô�!" << endl;

	// Ȯ�ο� �ڵ�
	cout << endl << "W �迭 �� Ȯ��" << endl << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << setw(10) << W[i][j] << " ";
		cout << endl << endl;
	}

	// �Լ� ����
	m_coloring(0);

	return 0;
}

// Algorithm 5.5 The Backtracking Algorithm for the m-Coloring Problem
// ���� : �����׷������� m���� ���� ����Ͽ� ������ ������ ���� ���� ���� �ʰ�
//        ������ ��ĥ�� �� �ִ� ��� ����� ���Ͻÿ�.
// �Է� : ���� ���� n�� m, �׸��� n���� ������ ���� �����׷���.
//        �׷����� ��� ���� �ε����� ��� 1���� n������ 2���� �迭 W�� ǥ���ȴ�.
//        ���⼭ i��° ������ j��° ���� ���̿� �������� �����ϸ� W[i][j]�� true�̰�,
//        �׷��� ������ false�̴�.
// ��� : �ִ�� m���� ���� ������ ������ ������ ���� ���� ���� �ʰ� �׷����� ��ĥ�ϴ� ������ ��� ���.
//        ����� �ε����� 1���� n������ �迭 vcolor�̴�. ���⼭ vcolor[i]���� i��° ������ �Ҵ�� ��
//        (1���� m ������ ����)�̴�.
void m_coloring(int i)
{
	int color;
	if (promising(i))
		if (i == n) {
			cout << "���� �߰�!" << endl;
			for(int i = 1; i <= n; i++)
				cout << vcolor[i] << " ";	// vcolor[1]���� vcolor[n]����
			cout << endl;
		}
		else
			for (color = 1; color <= m; color++) { // ���� ������ ��� ���� �õ��� ����.
				vcolor[i + 1] = color;
				m_coloring(i + 1);
			}
}

bool promising(int i) {
	int j;
	bool switch_val;
	switch_val = true;
	j = 1;
	while (j < i && switch_val) {	// ������ ������ �� ���� �̹� ĥ���� �ִ��� �����Ѵ�.
		if (W[i][j] && vcolor[i] == vcolor[j]) switch_val = false;
		j++;
	}
	return switch_val;
}