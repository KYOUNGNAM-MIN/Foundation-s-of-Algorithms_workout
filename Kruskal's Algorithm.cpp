// ���� �Է� ������ Version 
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; 

// n: Vertex�� ����, m: Edge�� ���� 
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

// Edge�� ������ �����ϱ� ���� Ŭ���� ����
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

// F: MST�� ����� Edge�� Solution Set�� ����, sum: MST�� ����ġ ����
vector<Edge> F;
int sum = 0;

/* kruskal �Լ� ���� 
 * �Է�: �������� n, �������� m, Edge�� ��� E, MST�� ����� Edge�� ���� F
 * ������ ����ġ�� �������� �������� ����, �ʱ⿣ F�� ������ 
 * initial(n): �� ������ ��Ʈ�� ����Ű�� ��Ʈ�� ����, �ʱ⿣ �ڱ� �ڽ��� ����Ŵ
 * F�� ��� Edge�� ������ n-1���� ���� ������ �ݺ��� ����
 * p = find(i): �� ���� i�� j�� ����Ű�� ��Ʈ ��带 ã�Ƴ��� p�� q�� ���� 
 * ���� p�� q�� �ٸ���, ���� �ٸ� ���տ� ���� ���̹Ƿ� merge(p, q) ����.
 * merge(p, q): �� Ʈ���� depth�� �������� depth�� ���� ���� ū ������ ������.
 * F�� �������� ������ ������ ���� 
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
	
	cout << "***MST�� ����� Solution F�� ��� ���� ����***" << endl;
	for(int i=0; i<F.size(); i++){
		cout << F[i].node[0] << "-----" << F[i].node[1] << endl;
	}
	cout << "\n";
	cout << "MST ����ġ ����: " << sum << endl;
	
	return 0;
}
