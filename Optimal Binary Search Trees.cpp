/* 교재 입력 데이터 Version */
#include <iostream>
using namespace std;

// Key의 개수 4개, 비교를 위한 초기 값 INF 
#define MAX 4
#define INF 99999

/* const string KeyOrderSet = {Don, Isabelle, Ralph, Wally}
 * 배열 P: 각 key가 검색될 확률 (0번째 인덱스는 비어놓기 위해 NULL 설정)
 * 배열 R: 언제 최소값이 선택되었는 지 알려주는 k 값(k가 root일때 최적)을 저장하는 배열.
 * minavg: key1~keyn 까지의 문제에서 구한 optimal한 Average Search Time의 최소값. 
 */
const float P[MAX+1] = {NULL, 3.0/8.0, 3.0/8.0, 1.0/8.0, 1.0/8.0};
int R[MAX+2][MAX+1];
float minavg;

// 시그마 begin~end 까지 확률 값(P 배열)을 계산하기 위한 함수.
float sumP(int begin, int end){
	float sum = 0;
	for(int i=begin; i<=end; i++)
		sum += P[i];
	return sum;
}

/* 매개변수-변수 n: key 개수, 배열 P: 각 key가 검색될 확률, 변수 minavg: A[1][n]값을 저장,
 * 			배열 R: 최솟값이 어느 경우(어떤 key가 root일 때)에 선택되었는 지 알려주는 k값 저장. 
 * 이때 최솟값과 최솟값을 만드는 k값을 저장할 배열 A와 배열 R을 구하는 것이 목적이므로,
 * 찾으려는 key 값이 아래 함수에 들어올 필요는 없다. 
 */
void optsearchtree(int n, const float P[MAX], float& minavg, int(*R)[MAX+1]){
	// 변수 선언 
	int i, j, k, diagonal;
	float tmp;
	// 각 경우의 수에 따른 Optimal한 Binary Search Tree의 평균 Search Time 값 저장할 배열 A 선언
	// 이때 행은 1 ~ 5, 열은 0 ~ 4로 보므로 행 한 줄 더 만듬.
	// 이 이유로 인해서, 위에서 선언한 배열 P의 첫 인덱스를 비워둬야 함.
	// 또한, 배열 R도 A와 같이 크기 설정함. 
	float A[n+2][n+1];
	
	// 배열 A와 R의 초기값,
	// A[i][i-1] = k가 i일 때, 첫 번째 노드가 root 일 때, 왼쪽 서브 트리 아무것도 없음. 
	// A[i][i] = 1개짜리 문제, 자기 자신의 확률 값. 
	for(i=1; i<=n; i++){
		A[i][i-1] = 0;
		A[i][i] = P[i];
		R[i][i] = i;
		R[i][i-1] = 0;
	}
	// A[n+1][n] = k가 n일 때,  마지막 노드가 root 일 때, 오른쪽 서브 트리는 아무것도 없음. 
	A[n+1][n] = 0; R[n+1][n] = 0;
	
	/* 3중 for문으로 경우의 수를 돌면서 배열 A와 R의 값 채워넣기. 
	 * A[i][j] = INF로 채워넣은 후, k에 대한 for문을 돌며, 
	 * 어떤 key가 root일 때 최소값이 되는 지 판단 후,
	 * 그 Optimal 값을 A[i][j]에 저장, 그 k값을 R[i][j]에 저장.
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
	
	// A 출력
	cout << "A 출력" << endl;
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
	// R 출력
	cout << "R 출력" << endl;
	for(i=1; i<=n+1; i++){
		for(j=0; j<=n; j++){
			if(i-j >= 2) cout << " " << " ";
			else cout << R[i][j] << " ";
		}
		cout << endl;
	}
	
	// key 1부터 n까지의 Optimal, Average Search Time이 최소인 것. 
	minavg = A[1][n];
}

int main(void){
	optsearchtree(MAX, P, minavg, R);
	
	printf("%.3lf\n", minavg);
	
	return 0;
}
