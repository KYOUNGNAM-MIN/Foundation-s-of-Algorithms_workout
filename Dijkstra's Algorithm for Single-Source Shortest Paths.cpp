// 교재 입력 데이터 version 
#include <iostream>
#include <vector>
using namespace std;

#define INF 9999999
#define SIZE 5

// 교재 입력 데이터 
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
	
	// touch: v1에서 출발하는 현재 최단경로의 마지막 정점을 v1로 초기화.
	// length: 그 경로의 길이는 v1에서의 Edge 상의 가중치로 초기화.
	for(i=2; i<=n; i++){
		touch[i] = 1;
		length[i] = W[0][i-1];
	}
	
	while(repeat < n-1){
		min = INF;
		// 최단 경로를 갖는 지 각 정점을 체크한다. 
		for(i=2; i<=n; i++){
			if(length[i]>=0 && length[i]<=min){
				min = length[i];
				vnear = i;
			}
		}
		
		// touch[vnear]가 인덱스인 정점에서 vnear가 인덱스인 정점으로 가는 Edge를 e에 저장.
		// e를 F에 추가함. 
		e.node[0] = touch[vnear];
		e.node[1] = vnear;
		e.weight = min;
		F.push_back(e);
		
		// Y에 속하지 않는 각 정점의 최단경로를 바꾼다.
		// vnear가 인덱스인 정점을 Y에 추가함.  
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
	
	cout << "***집합 F의 Edge 목록 출력***" << endl; 
	for(int i = 0; i<F.size(); i++){
		cout << "v" << F[i].node[0] << "-->" << "v" << F[i].node[1] << endl;
		cout << "v1~v" << F[i].node[1] << "까지의 최단경로의 길이 : " << F[i].weight << endl;
		cout << endl;
	}
	
	return 0;
}
