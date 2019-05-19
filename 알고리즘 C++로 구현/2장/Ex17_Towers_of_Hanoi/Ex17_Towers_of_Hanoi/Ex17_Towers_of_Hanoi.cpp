// 2장 연습문제 17번 하노이탑 문제를 푸는 분할정복 알고리즘 작성하기
/*

	하노이탑은 말뚝 3개와 크기가 모두 다른 구멍난 디스크 n개로 구성
	문제는 한 말뚝에 쌓여있는 n개의 디스크를 모두 지정한 말뚝으로 옮기는 것
	규칙 : (1) 세 개의 말뚝 이외에는 디스크를 놓을 수 없다.
	       (2) 한 번에 하나의 디스크만 옮길 수 있고, 말뚝의 맨 위에 있는 디스크만 옮길 수 있다.
		   (3) 큰 디스크를 작은 디스크 위에 올려놓을 수 없다.
*/

// 이 알고리즘의 시간복잡도는?

#include <iostream>
using namespace std;

void Towers_of_Hanoi(int n, int one, int two, int three)
{
	if (n > 0) {
		cout << "시작" << endl;
		Towers_of_Hanoi(n - 1, one, three, two);
		cout << one << " -> " << three << endl; // basic operation으로 두고 시간복잡도를 구해 보자!
		Towers_of_Hanoi(n - 1, two, one, three);
	}
}

int main()
{
	int n = 3; // 디스크 개수
	int one = 1;	// 첫번째 말뚝
	int two = 2;	// 두번째 말뚝
	int three = 3;	// 세번째 말뚝

	Towers_of_Hanoi(n, one, two, three);

	return 0;
}

