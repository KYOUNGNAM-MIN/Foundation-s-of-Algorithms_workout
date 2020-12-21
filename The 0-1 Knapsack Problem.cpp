#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define n 4
#define W 16

// first: p[], second: w[]
// item.first = price, item.second = weight
vector<pair<int, int> > item;
vector<string> bestset(n+1);
vector<string> include(n+1);

int maxprofit=0, gb_profit=0, gb_weight=0;
int numbest = 0;

// 아이템의 무게 당 가치를 기준으로 내림차순으로 정렬
bool cmp(const pair<int, int> &a, const pair<int, int> &b){
	return a.first/a.second > b.first/b.second;
}
 
bool promising(int i){
	int j, k;
	int totweight;
	float bound;
	
	if(gb_weight >= W) return false;
	else{
		j = i+1;
		bound = gb_profit;
		totweight = gb_weight;
		while((j<=n) && (totweight+item[j-1].second <= W)){
			totweight = totweight + item[j-1].second;
			bound = bound + item[j-1].first;
			j++;
		}
		k = j;
		if(k <= n){
			bound = bound + (W-totweight)*(item[k-1].first/item[k-1].second);
		}
		return bound > maxprofit;
	}
}

void knapsack(int i, int profit, int weight){
	if(weight <= W && profit > maxprofit){
		maxprofit = profit;
		numbest = i;
		copy(include.begin(), include.end(), bestset.begin());
	}
	
	if(promising(i)){
		include[i+1] = "YES";
		gb_profit = profit + item[i].first;
		gb_weight = weight+item[i].second;
		knapsack(i+1, profit+item[i].first, weight+item[i].second);
		
		include[i+1] = "NO";
		gb_profit = profit;
		gb_weight = weight;
		knapsack(i+1, profit, weight);
	}
}

int main(void){
	// 교재 입력 데이터 
	item.push_back(make_pair(40, 2));
	item.push_back(make_pair(30, 5));
	item.push_back(make_pair(50, 10));
	item.push_back(make_pair(10, 5));
	
	// p[i]/w[i]의 값이 큰 것부터 내림차순으로 정렬 
	sort(item.begin(), item.end(), cmp);
	
	knapsack(0, 0, 0);
	
	// bestset 내용 출력 
	cout << "-----BESTSET-----" << endl;
	for(int i=1; i<=n; i++){
		cout << bestset[i] << endl;
	}
	
	return 0;
}
