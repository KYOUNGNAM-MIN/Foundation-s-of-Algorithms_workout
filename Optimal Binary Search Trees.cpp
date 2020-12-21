/* ���� �Է� ������ Version */
#include <iostream>
using namespace std;

// Key�� ���� 4��, �񱳸� ���� �ʱ� �� INF 
#define MAX 4
#define INF 99999

/* const string KeyOrderSet = {Don, Isabelle, Ralph, Wally}
 * �迭 P: �� key�� �˻��� Ȯ�� (0��° �ε����� ������ ���� NULL ����)
 * �迭 R: ���� �ּҰ��� ���õǾ��� �� �˷��ִ� k ��(k�� root�϶� ����)�� �����ϴ� �迭.
 * minavg: key1~keyn ������ �������� ���� optimal�� Average Search Time�� �ּҰ�. 
 */
const float P[MAX+1] = {NULL, 3.0/8.0, 3.0/8.0, 1.0/8.0, 1.0/8.0};
int R[MAX+2][MAX+1];
float minavg;

// �ñ׸� begin~end ���� Ȯ�� ��(P �迭)�� ����ϱ� ���� �Լ�.
float sumP(int begin, int end){
	float sum = 0;
	for(int i=begin; i<=end; i++)
		sum += P[i];
	return sum;
}

/* �Ű�����-���� n: key ����, �迭 P: �� key�� �˻��� Ȯ��, ���� minavg: A[1][n]���� ����,
 * 			�迭 R: �ּڰ��� ��� ���(� key�� root�� ��)�� ���õǾ��� �� �˷��ִ� k�� ����. 
 * �̶� �ּڰ��� �ּڰ��� ����� k���� ������ �迭 A�� �迭 R�� ���ϴ� ���� �����̹Ƿ�,
 * ã������ key ���� �Ʒ� �Լ��� ���� �ʿ�� ����. 
 */
void optsearchtree(int n, const float P[MAX], float& minavg, int(*R)[MAX+1]){
	// ���� ���� 
	int i, j, k, diagonal;
	float tmp;
	// �� ����� ���� ���� Optimal�� Binary Search Tree�� ��� Search Time �� ������ �迭 A ����
	// �̶� ���� 1 ~ 5, ���� 0 ~ 4�� ���Ƿ� �� �� �� �� ����.
	// �� ������ ���ؼ�, ������ ������ �迭 P�� ù �ε����� ����־� ��.
	// ����, �迭 R�� A�� ���� ũ�� ������. 
	float A[n+2][n+1];
	
	// �迭 A�� R�� �ʱⰪ,
	// A[i][i-1] = k�� i�� ��, ù ��° ��尡 root �� ��, ���� ���� Ʈ�� �ƹ��͵� ����. 
	// A[i][i] = 1��¥�� ����, �ڱ� �ڽ��� Ȯ�� ��. 
	for(i=1; i<=n; i++){
		A[i][i-1] = 0;
		A[i][i] = P[i];
		R[i][i] = i;
		R[i][i-1] = 0;
	}
	// A[n+1][n] = k�� n�� ��,  ������ ��尡 root �� ��, ������ ���� Ʈ���� �ƹ��͵� ����. 
	A[n+1][n] = 0; R[n+1][n] = 0;
	
	/* 3�� for������ ����� ���� ���鼭 �迭 A�� R�� �� ä���ֱ�. 
	 * A[i][j] = INF�� ä������ ��, k�� ���� for���� ����, 
	 * � key�� root�� �� �ּҰ��� �Ǵ� �� �Ǵ� ��,
	 * �� Optimal ���� A[i][j]�� ����, �� k���� R[i][j]�� ����.
	 */
	for(diagonal=1; diagonal<=n-1; diagonal++){
		for(i=1; i<=n-diagonal; i++){
			j = i+diagonal;
			A[i][j] = INF;
			for(k=i; k<=j; k++){
				tmp = A[i][k-1] + A[k+1][j] + sumP(i, j);
				if(A[i][j] > tmp){
					A[i][j] = tmp;
					R[i][j] = k;
				}
			}
		}
	}
	
	// A ���
	cout << "A ���" << endl;
	for(i=1; i<=n+1; i++){
		for(j=0; j<=n; j++){
			if(i-j >= 2) cout << " " << " ";
			else{
				if(A[i][j]==0) cout << A[i][j] << " ";
				else printf("%.3lf ", A[i][j]);
			}
		}
		cout << endl;
	}
	// R ���
	cout << "R ���" << endl;
	for(i=1; i<=n+1; i++){
		for(j=0; j<=n; j++){
			if(i-j >= 2) cout << " " << " ";
			else cout << R[i][j] << " ";
		}
		cout << endl;
	}
	
	// key 1���� n������ Optimal, Average Search Time�� �ּ��� ��. 
	minavg = A[1][n];
}

int main(void){
	optsearchtree(MAX, P, minavg, R);
	
	printf("%.3lf\n", minavg);
	
	return 0;
}
