// 2�� �������� 17�� �ϳ���ž ������ Ǫ�� �������� �˰��� �ۼ��ϱ�
/*

	�ϳ���ž�� ���� 3���� ũ�Ⱑ ��� �ٸ� ���۳� ��ũ n���� ����
	������ �� ���ҿ� �׿��ִ� n���� ��ũ�� ��� ������ �������� �ű�� ��
	��Ģ : (1) �� ���� ���� �̿ܿ��� ��ũ�� ���� �� ����.
	       (2) �� ���� �ϳ��� ��ũ�� �ű� �� �ְ�, ������ �� ���� �ִ� ��ũ�� �ű� �� �ִ�.
		   (3) ū ��ũ�� ���� ��ũ ���� �÷����� �� ����.
*/

// �� �˰����� �ð����⵵��?

#include <iostream>
using namespace std;

void Towers_of_Hanoi(int n, int one, int two, int three)
{
	if (n > 0) {
		cout << "����" << endl;
		Towers_of_Hanoi(n - 1, one, three, two);
		cout << one << " -> " << three << endl; // basic operation���� �ΰ� �ð����⵵�� ���� ����!
		Towers_of_Hanoi(n - 1, two, one, three);
	}
}

int main()
{
	int n = 3; // ��ũ ����
	int one = 1;	// ù��° ����
	int two = 2;	// �ι�° ����
	int three = 3;	// ����° ����

	Towers_of_Hanoi(n, one, two, three);

	return 0;
}

