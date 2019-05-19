// coding by ������, 20150413
// Dijkstra's Algorithm for Single-Source Shortest Paths

#include <iostream>
#include <iomanip>
using namespace std;

// �������� ��Ÿ���� ����ü
struct edge {
	int index[2];	// (v1, v2)�� ǥ�� (������� �������� ǥ��)
	int weight;		// ����ġ�� ǥ��
};

// �������� ���� ����ü
struct set_of_edges {
	edge *edge_i;	// edge�� �迭(������) ����
};

// Algorithm 4.3 - Dijkstra's Algorithm
// ���� : ����ġ���� ����׷������� v1���� �ٸ� ��� ����� ���� �ִܰ�θ� ���Ͻÿ�.
// �Է� : ���� n(>=2)�� ���� n�� �ִ� ����� ����ġ���� ����׷���. 
//        �� �׷����� ������ �迭 W�� ǥ���Ǹ�, ��� ���� �ε����� ���� 1���� n�����̴�.
//        ���⼭ W[i][j]�� i��° ���𿡼� j��° ���� �մ� ������ ���� ����ġ�� �ȴ�.
// ��� : �ִܰ�� �� �����ִ� �������� ���� F
void dijkstra(int n, int **W, set_of_edges& F)
{
	int i, vnear, s;
	edge e;
	int *touch;	// touch[i] = Y�� ���� ����鸸 �߰��� ��ġ���� �Ͽ� v1���� vi�� ���� ���� �ִܰ�� ����
				//            ������ �������� <v,vi>��� �� ��, Y�� ���� ���� v�� �ε���
	touch = new int[n+1];
	int *length;	// length[i] = Y�� ���� ����鸸 �߰��� ��ġ���� �Ͽ� v1���� vi�� ���� ���� �ִܰ���� ����
	length = new int[n+1];

	// F�� ������
	for (i = 2; i <= n; i++) {	// �� ���� ���ؼ�
		touch[i] = 1;				// v1���� ����ϴ� ���� �ִܰ���� ������ ����
		length[i] = W[0][i-1];		// v1���� �ʱ�ȭ�Ѵ�.

		if (W[0][i-1] == -1)
			length[i] = 987654321;	// ��û ū ���� ����

	}								// �� ����� ���̴� v1������ ������ ���� ����ġ��
									// �ʱ�ȭ�Ѵ�.
	
	// Ȯ�ο� �ڵ�
	/*
	cout << "touch�� length[i] ���� �Ϸ�!" << endl;
	for (int j = 0; j <= n; j++)
	{
		cout << "touch[" << j << "]: " << touch[j] << endl;
		cout << "length[" << j << "]: " << length[j] << endl;
	}
	*/
	for(s = 1; s <= n - 1; s++) {	// n-1�� �ݺ�
		// cout << "�ݺ� ����!" << endl;
		// cout << "s���� " << s << endl;
		int min = 987654321; // ��û ū ���� ����
		for (i = 2; i <= n; i++) {	// �ִܰ�θ� �������� �� ���� �����Ѵ�.
			if ((0 < length[i]) && (length[i] < min)) {
				min = length[i];
				vnear = i;
			}
		}

		// e = touch[vnear]�� �ε����� ���𿡼� vnear�� �ε����� ����� ���� ������;
		e.index[0] = touch[vnear];
		e.index[1] = vnear;
		e.weight = min;
		// e�� F�� �߰�;
		F.edge_i[s].index[0] = e.index[0];
		F.edge_i[s].index[1] = e.index[1];
		F.edge_i[s].weight = min;

		// cout << "e�� F�� �߰�!" << endl;

		for (i = 2; i <= n; i++) {
			// cout << "i�� �� " << i << endl;
			// cout << "vnear�� �� " << vnear << endl;
			if (W[vnear - 1][i - 1] != -1 && length[vnear] != -1) {
				if (length[vnear] + W[vnear - 1][i - 1] < length[i]) {
					length[i] = length[vnear] + W[vnear - 1][i - 1];
					// cout << "length[i]�� �Ҵ� ����! length[i] " << length[i] << endl;
					touch[i] = vnear;			// Y�� ������ �ʴ� �� ���� ���ؼ�,
					// cout << "touch[i]�� �Ҵ� ����! touch[i] " << touch[i] << endl;
				}								// �ִܰ�θ� �ٲ۴�.
			}
		}

		length[vnear] = -1;				// vnear�� �ε����� ���� Y�� �߰��Ѵ�.
		// cout << "length[vnear]�� �Ҵ� ����! length[vnear] " << length[vnear] << endl;
		// cout << "�ϳ� ��!" << endl;
	}
}

int main()
{
	// ����ڷκ��� �׷����� �Է¹޴´�.	
	int Vertex;		// ����(����)�� ����
	cout << "���ݺ��� ��������� �ִܰ�� ������ Ǯ�� ���ڽ��ϴ�!" << endl;
	cout << "��������� �ִܰ�� ������ Ǯ �׷����� �Է��� �ּ���!" << endl;

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
		}
	}


	// Ȯ�ο� �ڵ�
	cout << endl << "W �迭 �� Ȯ��" << endl << endl;
	for (int i = 0; i < Vertex; i++) {
		for (int j = 0; j < Vertex; j++)
			cout << setw(10) << W[i][j] << " ";
		cout << endl << endl;
	}


	set_of_edges output;
	output.edge_i = new edge[Vertex];

	// cout << "���ͽ�Ʈ�� �Լ� ȣ�� ����!" << endl;
	// ���ͽ�Ʈ�� �Լ� ȣ��
	dijkstra(Vertex, W, output);
	// cout << "���ͽ�Ʈ�� �Լ� ȣ�� ��!" << endl;	

	// ���� F ���
	cout << endl << "�������� ������ ������ �����ϴ�!" << endl << endl;
	for (int i = 1; i < Vertex; i++)
	{
		cout << i << "��° output.edges" << endl;
		cout << output.edge_i[i].index[0] << " " << output.edge_i[i].index[1] << endl;
		cout << i << "��° output.weight" << endl;
		cout << output.edge_i[i].weight << endl;
	}
}