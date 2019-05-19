#include <iostream>
using namespace std;
#define SIZE 13

int location(int low, int high);

const int S[SIZE+1] = { -1, 10, 12, 13, 14, 18, 20, 25, 27, 30, 35, 40, 45, 47 };
int x = 18;

int main()
{
	int locationout;
	int n = sizeof(S) / sizeof(S[0]);
	locationout = location(1, n);
	cout << locationout;

	return 0;
}

// Binary Search
// ���� : ���Ұ� n���� ���ĵ� �迭 S�� �˻�Ű x�� �ִ°�?
// �Է� : ���� ���� n, ���ĵ�(�񳻸�����) �迭 S(÷�ڴ� 1���� n����), �˻�Ű x
// ��� : location, S���� x�� ��ġ(���� x�� s�� ������ 0)
int location(int low, int high)
{
	int mid;

	if (low > high)
		return 0;					// ã�� ������  
	else
	{
		mid = (low + high) / 2;		// ���� ������(������ ����)
		if (x == S[mid])
			return mid;				// ã����
		else if (x < S[mid])		// S[]�� ���� �迭�� ����
			return location(low, mid - 1);	// ���� ���� ������
		else
			return location(mid + 1, high);	// ������ ���� ������
	}
}