// ���� �Է� ������ version 
#include <iostream>
#include <vector>
using namespace std;

#define INF 9999999
#define SIZE 5

// ���� �Է� ������ 
int W[SIZE][SIZE] = {
	{0,7,4,6,1},
	{INF,0,INF,INF,INF},
	{INF,2,0,5,INF},
	{INF,3,INF,0,INF},
	{INF,INF,INF,1,0}
};

class Edge{
	public:
		int node[2];
		int weight;
};

vector<Edge> F;
void dijkstra(int n, const int W[][SIZE], vector<Edge>& F){
	int i, vnear, min;
	int repeat = 0;
	int touch[n+1];
	int length[n+1];
	Edge e;
	
	// touch: v1���� ����ϴ� ���� �ִܰ���� ������ ������ v1�� �ʱ�ȭ.
	// length: �� ����� ���̴� v1������ Edge ���� ����ġ�� �ʱ�ȭ.
	for(i=2; i<=n; i++){
		touch[i] = 1;
		length[i] = W[0][i-1];
	}
	
	while(repeat < n-1){
		min = INF;
		// �ִ� ��θ� ���� �� �� ������ üũ�Ѵ�. 
		for(i=2; i<=n; i++){
			if(length[i]>=0 && length[i]<=min){
				min = length[i];
				vnear = i;
			}
		}
		
		// touch[vnear]�� �ε����� �������� vnear�� �ε����� �������� ���� Edge�� e�� ����.
		// e�� F�� �߰���. 
		e.node[0] = touch[vnear];
		e.node[1] = vnear;
		e.weight = min;
		F.push_back(e);
		
		// Y�� ������ �ʴ� �� ������ �ִܰ�θ� �ٲ۴�.
		// vnear�� �ε����� ������ Y�� �߰���.  
		for(i=2; i<=n; i++){
			if(length[vnear] + W[vnear-1][i-1] < length[i]){
				length[i] = length[vnear] + W[vnear-1][i-1];
				touch[i] = vnear;
			}
		}
		length[vnear] = -1;
		repeat++;
	}
}

int main(void){
	dijkstra(SIZE, W, F);
	
	cout << "***���� F�� Edge ��� ���***" << endl; 
	for(int i = 0; i<F.size(); i++){
		cout << "v" << F[i].node[0] << "-->" << "v" << F[i].node[1] << endl;
		cout << "v1~v" << F[i].node[1] << "������ �ִܰ���� ���� : " << F[i].weight << endl;
		cout << endl;
	}
	
	return 0;
}
