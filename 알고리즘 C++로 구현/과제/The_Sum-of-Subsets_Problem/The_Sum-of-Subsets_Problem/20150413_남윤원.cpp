// coding by ������, 20150413
// The Backtracking Algorithm for the Sum-of-Subsets Problem

#include <iostream>
using namespace std;

// ������ ����, n, *w, W, *include�� �� ���ν����� �Է��� �ƴϴ�.
// ��, �� �������� ���������� �����Ѵ�.
int n;			// ���� ������ ����
int *w;			// (�������� �ʴ� ������) ���ĵ� ���� ������ �迭 (������ 1���� n)
int W;			// ��ǥ�� �ϴ� ���� ���� W
int *include;	// ������� ����� �迭

// �Լ� ���� ����
void sum_of_subsets(int i, int weight, int total);
bool promising(int i, int weight, int total);


int main()
{
	int total = 0;
	cout << "���ݺ��� �κ������� �� ���ϱ� ������ Ǯ�� ���ڽ��ϴ�!" << endl;
	cout << "�� ���α׷���, ���� W�� �Ǵ� ��� ������ ������ ���ϰ� �˴ϴ�." << endl;
	cout << "��ǥ�� �ϴ� ���� ���� W�� �Է��ϼ���!" << endl;
	cin >> W;
	cout << "��ǥ�� �ϴ� ���� ���� W�� " << W << " �Դϴ�!" << endl;
	cout << "��������, ������ �������� �Է¹ް��� �մϴ�! �� ���� ������ �������� �ִ��� �Է��ϼ���!" << endl;
	cin >> n;
	w = new int[n + 1];			// �迭(������) w�� n+1�� ũ�⸸ŭ ���� �Ҵ�
	include = new int[n + 1];	// �迭(������) include�� n+1�� ũ�⸸ŭ ���� �Ҵ�
	cout << "���ݺ��� " << n << " ���� �������� �Է¹ްڽ��ϴ�! ������������ �Է��� �ּ���!" << endl;
	for (int i = 1; i <= n; i++)
	{
		cin >> w[i];
		total = total + w[i];
	}
	sum_of_subsets(0, 0, total);

	return 0;
}

// Algorithm 5.4 The Backtracking Algorithm for the Sum-of-Subsets Problem
// ���� : n�� ���� ����(����)�� ���� ���� W�� ������, ���� W�� �Ǵ� ��� ������ ������ ��� ���ϱ�
// �Է� : ���� ���� n, (�������� �ʴ� ������) ���ĵ� ���� ������ �迭 w(������ 1���� n), ���� ���� W
// ��� : ���� W�� �Ǵ� ��� ������ ����
// sum_of_subsets ���� ȣ��: sum_of_subsets(0, 0, total);
void sum_of_subsets(int i, int weight, int total)
{
	//cout << "i : " << i << endl;
	//cout << "weight : " << weight << endl;
	//cout << "total : " << total << endl;
	if (promising(i, weight, total))
	{
		if (weight == W)
		{
			cout << endl << "ã�Ҵ�!" << endl;
			for (int p = 1; p <= i; p++)
			{
				cout << include[p] << " ";
			}
			cout << endl;
		}
		else {
			include[i + 1] = w[i + 1]; // 'yes' // w[i+1]�� �����Ѵ�.
			sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1]);
			include[i + 1] = 0;	// 'no' // w[i+1]�� �������� �ʴ´�.
			sum_of_subsets(i + 1, weight, total - w[i + 1]);
		}
	}
}

// � ��尡 �������� �ƴ����� �Ǵ��ϴ� �Լ�
bool promising(int i, int weight, int total)
{
	// cout << ((weight + total >= W) && (weight == W || weight + w[i + 1] <= W)) << endl;
	return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}
