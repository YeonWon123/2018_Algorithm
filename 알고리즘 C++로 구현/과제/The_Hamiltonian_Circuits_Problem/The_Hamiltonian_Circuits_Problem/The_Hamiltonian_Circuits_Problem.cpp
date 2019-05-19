// coding by 20150413 ������
// The Hamiltonian Circuits Problem

#include <iostream>
using namespace std;

int n;			// ������ ����(���� ����)
int **W;		// �Է¹��� ����� �׷���
int *vindex;	// ������� ������ �迭(������)

void hamiltonian(int i);
bool promising(int i);


int main()
{
	// ����ڷκ��� ����� �׷����� �Է¹޴´�.	
	cout << "���ݺ��� �ع�ư ȸ�� ������ Ǯ�� ���ڽ��ϴ�!" << endl;
	cout << "����� �׷����� �Է��� �ּ���!" << endl;

	cout << "�� ���� ������ �ֳ���? ";
	cin >> n;
	cout << "������ " << n << "���� �����Ǿ����ϴ�!" << endl;

	// �Է¹��� ������ ����(n)��� ������� ������ �迭(������) vcolor�� ���� �Ҵ��Ѵ�.
	vindex = new int[n];

	// �Է¹��� ������ ����(n)��� �����͸� �Է¹��� 2���� �迭(���� ������) W�� ���� �Ҵ��Ѵ�.
	W = new int*[n + 1];
	for (int i = 1; i <= n; i++)
		W[i] = new int[n + 1];

	cout << "������(edge)�� ���� ������ �ִ����� ���θ� �Է��� �ּ���!" << endl;
	cout << "������ ������ 1, ������ ���� ������ 0�Դϴ�." << endl;
	cout << "�ڱ� �ڽ��� ������ ���� �ʴٰ� �����ϰ�, 0���� �Է��Ͽ� �ּ���." << endl;

	for (int i = 1; i <= n; i++) {
		cout << "V" << i << "���� �� edge�� ������ �ִ��� ���� : ";
		for (int j = 1; j <= n; j++)
		{
			cin >> W[i][j];
		}
	}

	// �Լ� ȣ��
	vindex[0] = 1;	// v1�� ����������� �Ѵ�.
	hamiltonian(0);

	return 0;
}

// Algorithm 5.6 The Backtracking Algorithm for the Hamiltonian Circuits Problem
// ���� : ����� �����׷������� �ع�ư ȸ�θ� ��� ���Ͻÿ�.
// �ع��� ��� : �� �������� ����Ͽ�, �ٸ� ��� ������ �ѹ��� ��ġ��, �ٽ� ���� �������� ���ƿ��� ���
// �Է� : ���� ���� n�� ������ n���� �����׷���. �׷����� 2���� �迭 W�� ǥ���Ѵ�.
//        �� �迭�� ��� ���� �ε����� 1���� n�����̴�. ���⼭ i° ������ j° ������ �մ� �������� ������
//        W[i][j] ���� true�̰�, �׷��� ������ false�̴�.
// ��� : �־��� �������� ����Ͽ� �׷������� �� ������ ��Ȯ�� �� ���� �湮�ϰ�, ��� �������� ���ƿ��� ��� ���.
//        �� ����� ����� �ε����� 0���� n-1������ �ε����� �迭 vindex�̴�.
//        ���⼭ vindex[i]�� ��λ󿡼� i° ������ �ε����̴�.
//        ��� ������ �ε����� vindex[0]�̴�.
void hamiltonian(int i)
{
	int j;

	if (promising(i))
		if (i == n - 1) {
			cout << "�ع��� ȸ�θ� ã�Ҵ�!" << endl;
			for(int i = 0; i < n; i++)
				cout << vindex[i] << " ";
			cout << endl;
		}
		else
			for (j = 2; j <= n; j++) {	// ��� ������ ���� ������ �õ��� ����.
				vindex[i + 1] = j;
				hamiltonian(i + 1);
			}
}

bool promising(int i)
{
	int j;
	bool switch_val;

	if (i == n - 1 && !W[vindex[n - 1]][vindex[0]]) // ù° ������ ������ ������
		switch_val = false;							// �����ؾ� �ϰ�,
	else if (i > 0 && !W[vindex[i - 1]][vindex[i]])	// i° ������ (i-1)° ������
		switch_val = false;							// �����ؾ� �Ѵ�.
	else {
		switch_val = true;
		j = 1;
		while (j < i && switch_val) {				// ������ �̹� ���õǾ������� �˻��Ѵ�.
			if (vindex[i] == vindex[j])
				switch_val = false;
			j++;
		}
	}
	return switch_val;
}