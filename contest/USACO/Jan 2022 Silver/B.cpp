#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vpi = vector<pii>;
using vpl = vector<pll>;

#define all(x) (int)(x).size()
#define fi first
#define se second
#define pb push_back

const int INF = 1e9;
const ll LINF = 1e18;


void solve(){
	int n;
	cin >> n;
	vi h(n), L(n), R(n);
	for (int i=0;i<n;++i){
		cin >> h[i];
	}
	/*
		Using a stack to find the maximum interval for each cow
		in which the cow has the maximum height amongst all cows
	*/
	stack<int> st;
	for (int i=0;i<n;++i){
		while(!st.empty()&&h[st.top()]<h[i]) st.pop();
		L[i] = (st.empty()? -1: st.top());
		st.push(i);
	}
	while(!st.empty()) st.pop();
	for (int i=n-1;i>=0;--i){
		while(!st.empty()&&h[st.top()]<h[i]) st.pop();
		R[i] = (st.empty()? n: st.top());
		st.push(i);
	}
	ll ans = 0;
	for (int i=0;i<n;++i){
		if (L[i]>=0) ans += i-L[i]+1;
		if (R[i]<n) ans+=R[i]-i+1;
	}
	cout << ans << "\n";
	
}

int main(){
	cin.tie(0)->sync_with_stdio(0);
	solve();
	return 0;
}