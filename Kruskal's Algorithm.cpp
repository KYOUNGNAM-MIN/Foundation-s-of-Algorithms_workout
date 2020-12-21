// 교재 입력 데이터 Version 
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; 

// n: Vertex의 개수, m: Edge의 개수 
const int n = 5;
const int m = 7;

// Disjoint Set Data Structure 2
typedef int index;
typedef index set_pointer;

struct nodetype{
	index parent;
	int depth;
};
typedef nodetype universe[n+1];
universe U;

void makeset(index i){
	U[i].parent = i;
	U[i].depth = 0;
}
set_pointer find(index i){
	index j = i;
	while(U[j].parent != j)
		j = U[j].parent;
	return j;
}
void merge(set_pointer p, set_pointer q){
	if(U[p].depth == U[q].depth){
		U[p].depth = U[p].depth + 1;
		U[q].parent = p;
	}
	else if(U[p].depth < U[q].depth)
		U[p].parent = q;
	else
		U[q].parent = p;
}
bool equal(set_pointer p, set_pointer q){
	if(p == q) return true;
	else return false;
}
void initial(int n){
	index i;
	for(i=1; i<=n; i++){
		makeset(i);
	}
}

// Edge의 정보를 저장하기 위한 클래스 생성
class Edge{
	public:
		int node[2];
		int weight;
		Edge(){}
		Edge(int a, int b, int weight){
			this->node[0] = a;
			this->node[1] = b;
			this->weight = weight;
		}
		bool operator <(Edge &edge){
			return this->weight < edge.weight;
		}
};

// F: MST를 만드는 Edge의 Solution Set을 저장, sum: MST의 가중치 총합
vector<Edge> F;
int sum = 0;

/* kruskal 함수 구현 
 * 입력: 정점개수 n, 간선개수 m, Edge가 담긴 E, MST를 만드는 Edge를 담을 F
 * 간선의 가중치를 기준으로 오름차순 정렬, 초기엔 F는 공집합 
 * initial(n): 각 정점의 루트가 가리키는 루트를 저장, 초기엔 자기 자신을 가리킴
 * F에 담긴 Edge의 개수가 n-1보다 작을 때까지 반복문 실행
 * p = find(i): 각 정점 i와 j가 가리키는 루트 노드를 찾아내서 p와 q에 저장 
 * 만약 p와 q가 다르면, 서로 다른 집합에 속한 것이므로 merge(p, q) 수행.
 * merge(p, q): 두 트리의 depth를 기준으로 depth가 작은 것이 큰 곳으로 합쳐짐.
 * F에 합쳐지는 간선의 정보를 저장 
 */
void kruskal(int n, int m, vector<Edge> E, vector<Edge>& F){
	index i, j;
	set_pointer p, q;
	Edge e;
	
	sort(E.begin(), E.end());
	F.clear();
	initial(n);
	
	int tmp = 0;
	while(F.size() < n-1){
		e = E[tmp];
		i = e.node[0];
		j = e.node[1];
		p = find(i);
		q = find(j);
		if(!equal(p, q)){
			merge(p, q);
			F.push_back(e);
			sum += e.weight;
		}
		tmp++;
	}
}

int main(void){
	vector<Edge> v;
	v.push_back(Edge(1,2,1));
	v.push_back(Edge(1,3,3));
	v.push_back(Edge(2,3,3));
	v.push_back(Edge(2,4,6));
	v.push_back(Edge(3,4,4));
	v.push_back(Edge(3,5,2));
	v.push_back(Edge(4,5,5));
	
	kruskal(n, m, v, F);
	
	cout << "***MST를 만드는 Solution F에 담긴 간선 정보***" << endl;
	for(int i=0; i<F.size(); i++){
		cout << F[i].node[0] << "-----" << F[i].node[1] << endl;
	}
	cout << "\n";
	cout << "MST 가중치 총합: " << sum << endl;
	
	return 0;
}
