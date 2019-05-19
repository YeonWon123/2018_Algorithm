// coding by ������, 20150413 
// Kruskal's Algorithm
// ���� ��� : C++

#include "Disjoint_Set_Data_Structure.h"
#include "Kruskal's_algorithm.h"
#include "QuickSort.h"
#include <iomanip>

int main()
{
	// ---------------------------------------------------------------------------------
	// 1. ����ڷκ��� �׷����� �Է¹޴´�. �̶� �������� ���� count�Ѵ�.
	// ---------------------------------------------------------------------------------

	int Vertex;		// ����(����)�� ����
	int Edge_count = 0;	// �������� ����
	cout << "���ݺ��� �ּҺ�� ����Ʈ��(MST)�� ���غ��ڽ��ϴ�!" << endl;
	cout << "�ּҺ�� ����Ʈ���� ���� �׷����� �Է��� �ּ���!(��, ����⼺ �׷������� �մϴ�.)" << endl;

	cout << "�� ���� ����(Vertex)�� �ֳ���? ";
	cin >> Vertex;
	cout << "Vertex�� " << Vertex << "���� �����Ǿ����ϴ�!" << endl;

	// �Է¹��� Vertex�� ũ���� �����͸� �Է¹��� 2���� �迭(���� ������) W�� ���� �Ҵ��Ѵ�.
	int **W = new int*[Vertex];
	for (int i = 0; i < Vertex; i++)
		W[i] = new int[Vertex];

	cout << "������(edge)�� ����ġ(weight)�� �Է��� �ּ���!" << endl;
	cout << "����ġ(weight)�� ���Ѵ��� ��� -1�Դϴ�." << endl;
	cout << "�ڱ� �ڽ��� ����ġ(weight)�� 0���� �մϴ�." << endl;

	for (int i = 0; i < Vertex; i++) {
		cout << "V" << i + 1 << "���� �� edge�� ���� weight : ";
		for (int j = 0; j < Vertex; j++)
		{
			cin >> W[i][j];
			if (W[i][j] > 0) // ����ġ�� 0�� �ƴ� ��� �������� �ִٴ� ���̹Ƿ�
				Edge_count++;		 // Edge�� 1 ������Ų��.
		}
	}
	
	Edge_count = Edge_count / 2; // ����⼺ �׷����̹Ƿ�, Edge�� 2���� ���������Ƿ� ������ 2�� ���ش�.

	// Ȯ�ο� �ڵ�
	cout << endl << "W �迭 �� Ȯ��" << endl << endl;
	for (int i = 0; i < Vertex; i++) {
		for (int j = 0; j < Vertex; j++)
			cout << setw(10) << W[i][j] << " ";
		cout << endl << endl;
	}
	

	// ---------------------------------------------------------------------------------
	// 2. �Է¹��� �׷�������, �������� �� ����ġ��, set_of_edges ����ü ���� �ȿ� �ִ´�.
	// ---------------------------------------------------------------------------------

	// ���� set_of_edges ����ü������ �����Ѵ�.
	set_of_edges input;
	
	// ������ ������ ����ü����(input) ���� �迭(������)���� Edge�� ����+1��ŭ �����Ҵ����ش�.
	// Edge�� ����+1��ŭ �����Ҵ����ִ� ������ �ε����� 1���� ����� ���̱� �����̴�.
	// �� ��, weight�� Edges ������ ���� ���� �Ҵ����ش�.
	input.weight = new int[Edge_count+1];
	input.Edges = new int*[Edge_count+1];
	for (int i = 1; i <= Edge_count; i++)
		input.Edges[i] = new int[2];     // (v1, v2)�� ���� ǥ���ϱ� ���ؼ��� �迭�� ũ�Ⱑ 2��� ����ϴ�.

	// ���� �Է¹��� �׷������� �������� �� ����ġ�� input�� �ִ´�.
	int k = 1;	// input.weight�� input.Edges�� �ε����� 1���� ����
	for (int i = 0; i < Vertex; i++)
	{
		for (int j = i+1; j < Vertex; j++)
		{
			if (W[i][j] > 0)
			{
				input.weight[k] = W[i][j];
				input.Edges[k][0] = i+1;
				input.Edges[k][1] = j+1;
				k++;
			}
		}
	}
	/*
	// Ȯ�ο� �ڵ�
	for (int i = 1; i <= Edge_count; i++)
	{
		cout << i << "��° input.Edges" << endl;
		cout << input.Edges[i][0] << " " << input.Edges[i][1] << endl;
		cout << i << "��° input.weight" << endl;
		cout << input.weight[i] << endl;
	}
	*/


	// ---------------------------------------------------------------------------------
	// 3. Kruskal's algorithm�� �̿��Ͽ� �ּҺ�� ����Ʈ��(MST)�� ���Ѵ�.
	// ---------------------------------------------------------------------------------

	// output�� MST���� �������� ������ �����ϴ� ������ �� ���̴�.
	// MST���� �������� ���� Vertex-1�̹Ƿ�, F�� Vertex-1�� ũ�⸸ŭ ���� �Ҵ����ش�.
	// �� ��, weight�� Edges ������ ���� ���� �Ҵ����ش�.
	set_of_edges output;
	output.weight = new int[Vertex];
	output.Edges = new int*[Vertex];
	for (int i = 1; i < Vertex; i++)
		output.Edges[i] = new int[2];	// (v1, v2)�� ���� ǥ���ϱ� ���ؼ��� �迭�� ũ�Ⱑ 2��� ����ϴ�.

	// ũ�罺Į �˰����� �����Ͽ� output�� ������� ����ǰ� �Ѵ�.
	// �� MST���� �������� ������ output�� ����ǰ� �Ѵ�.
	Kruskal(Vertex, Edge_count, input, output);

	// MST����, �������� ������ ����� output�� ����� ����.

	cout << endl << "�������� ������ ������ �����ϴ�!" << endl << endl;
	for (int i = 1; i < Vertex; i++)
	{
		cout << i << "��° output.Edges" << endl;
		cout << output.Edges[i][0] << " " << output.Edges[i][1] << endl;
		cout << i << "��° output.weight" << endl;
		cout << output.weight[i] << endl;
	}
}