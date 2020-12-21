/* ���� �Է� ������ Version */
#include <iostream>
using namespace std;

// ����� ���� MAX, �� �� �ִ밪���� �Է��� INF ��
#define MAX 6
#define INF 99999

// �� ����� ũ�� ex) A0 = D[0]*D[1]
int D[MAX+1] = {5,2,3,4,6,7,8};
// i~j������ ���� ���� intermediate point 
int P[MAX][MAX];
// �־��� ��� �� i~j������ ���� �� �ʿ��� �ּ� ���� ���� Ƚ�� 
int M[MAX][MAX];

// �Ű�����: ����� ���� n, �� ����� ũ�� D, �ּ� ���� �� intermediate point�� P 
int minmult(int n, const int D[MAX], int(*P)[MAX]){
	int i, j, k, diagonal, tmp;
	
	// �ڱ� �ڽ��� �ּ� ���� ���� Ƚ���� 0�̹Ƿ� 0���� �ʱ�ȭ. 
	for(i=0; i<n; i++)
		M[i][i] = 0;
	
	/*
	M[i][j]�� ���Ѵ� ������ ������ INF�� ����.
	���� k�� ������Ű�鼭 M[i][k] + M[k+1][j] + D[i]*D[k+1]*D[j+1] ����
	M[i][j]���� ������ �� ���� ���� M[i][j]�� ����.
	�ּڰ��� ���Ե� ���� k���� P[i][j]�� ����. 
	*/
	for(diagonal=1; diagonal < n; diagonal++){
		for(i=0; i < n-diagonal; i++){
			j = i + diagonal;
			M[i][j] = INF;
			for(k=i; k<j; k++){
				tmp = M[i][k] + M[k+1][j] + D[i]*D[k+1]*D[j+1];
				if(M[i][j] > tmp){
					M[i][j] = tmp;
					P[i][j] = k;
				}
			}
		}
	}
	
	// 3�� for������ ���� �ּ� ���� Ƚ�� ���. 
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(i==j) printf("%8d",M[i][j]);
			else if(j>=i) printf("%5d(%d)",M[i][j],P[i][j]);
			else printf("%8s","NULL");
		}
		printf("\n");
	}
	
	return M[0][n-1];
}

// Ai x ... x Aj �� ����� �����ϴµ�
// �⺻���� ������ ���� ���� ���� ��� ������� ��ȣ�� �ļ� ��� 
void order(int i, int j){
	// order ��� �Լ� �����ϴ� ���� 
	if(i==j)
		cout << "A" << i;
	else{
		int k = P[i][j];
		cout << "(";
		order(i,k);
		order(k+1,j);
		cout << ")";
	}
}

int main(void){
	int a = minmult(MAX, D, P);
	printf("Min: %d\n", a);
	order(0, MAX-1);
	
	return 0;
}
