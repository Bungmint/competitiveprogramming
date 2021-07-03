#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pi = pair<int,int>;
using pl = pair<ll,ll>;
using vpi = vector<pi>;

#define sz(x) (int)x.size()
#define all(v) (v).begin(), (v).end()
#define fi first
#define se second
#define ar array
#define pb push_back
#define lb lower_bound

const int INF = 1e9;
const int N = 1e5+1;
int pref[N];

void setIO(string s){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	freopen((s+".in").c_str(), "r", stdin);
	freopen((s+".out").c_str(), "w",stdout);
}

void solve(){
	int n, k, b;
	cin >> n >> k >> b;
	for (int i=0;i<b;++i){
		int t;
		cin >> t;
		pref[t]++;
	}
	for (int i=1;i<=n;++i) pref[i]+=pref[i-1];
	int ans = INF;
	for (int i=k;i<=n;++i){
		ans = min(ans, pref[i]-pref[i-k]);
	}
	cout << ans << "\n";
}


int main(){
	setIO("maxcross");
	solve();
}


