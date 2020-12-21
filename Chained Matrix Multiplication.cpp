/* 교재 입력 데이터 Version */
#include <iostream>
using namespace std;

// 행렬의 개수 MAX, 비교 전 최대값으로 입력할 INF 값
#define MAX 6
#define INF 99999

// 각 행렬의 크기 ex) A0 = D[0]*D[1]
int D[MAX+1] = {5,2,3,4,6,7,8};
// i~j까지의 곱셈 시의 intermediate point 
int P[MAX][MAX];
// 주어진 행렬 중 i~j까지의 곱셈 시 필요한 최소 곱셈 연산 횟수 
int M[MAX][MAX];

// 매개변수: 행렬의 개수 n, 각 행렬의 크기 D, 최소 곱셈 시 intermediate point인 P 
int minmult(int n, const int D[MAX], int(*P)[MAX]){
	int i, j, k, diagonal, tmp;
	
	// 자기 자신의 최소 곱셈 연산 횟수는 0이므로 0으로 초기화. 
	for(i=0; i<n; i++)
		M[i][i] = 0;
	
	/*
	M[i][j]에 무한대 값으로 정의한 INF를 대입.
	이후 k를 증가시키면서 M[i][k] + M[k+1][j] + D[i]*D[k+1]*D[j+1] 값이
	M[i][j]보다 작으면 그 작은 값을 M[i][j]에 대입.
	최솟값이 대입될 때의 k값을 P[i][j]에 대입. 
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
	
	// 3중 for문으로 구한 최소 곱셈 횟수 출력. 
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

// Ai x ... x Aj 의 계산을 수행하는데
// 기본적인 곱셈의 수가 가장 적게 드는 순서대로 괄호를 쳐서 출력 
void order(int i, int j){
	// order 재귀 함수 종료하는 조건 
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
