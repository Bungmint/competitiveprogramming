// Problem: Another Game
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/2208
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		int n;
		scanf("%d", &n);
		int t;
		bool odd=0;
		for (int i=0;i<n;++i) scanf("%d", &t), odd|=(t&1);
		if (odd) puts("first");
		else puts("second");
	}
}