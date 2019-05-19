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
// 문제 : 원소가 n개인 정렬된 배열 S에 검색키 x가 있는가?
// 입력 : 양의 정수 n, 정렬된(비내림차순) 배열 S(첨자는 1부터 n까지), 검색키 x
// 출력 : location, S에서 x의 위치(만약 x가 s에 없으면 0)
int location(int low, int high)
{
	int mid;

	if (low > high)
		return 0;					// 찾지 못했음  
	else
	{
		mid = (low + high) / 2;		// 정수 나눗셈(나머지 버림)
		if (x == S[mid])
			return mid;				// 찾았음
		else if (x < S[mid])		// S[]는 전역 배열로 선언
			return location(low, mid - 1);	// 왼쪽 반을 선택함
		else
			return location(mid + 1, high);	// 오른쪽 반을 선택함
	}
}