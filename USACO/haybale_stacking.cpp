#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pi = pair<int,int>;
using pl = pair<ll, ll>;

#define sz(x) (int)x.size()
#define ar array
#define all(v) (v).begin() (v).end()
#define pb push_back
#define lb lower_bound
#define fi first
#define se second

const int N = 1e6+10;
int pref[N];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, k;
	cin >> n >> k;
	while(k--){
		int a, b;
		cin >> a >> b;
		pref[a]++;
		pref[b+1]--;
	}
	for (int i=1;i<=n;++i) pref[i] += pref[i-1];
	sort(pref+1, pref+n+1);
	cout << pref[(n+1)/2]<<"\n";
}