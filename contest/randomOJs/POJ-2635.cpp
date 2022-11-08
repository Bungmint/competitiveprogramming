#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 1e9;
const int MOD = 1e9 + 7; //998244353
const int MAXN = 1e6+1;
vector<int> prime;
bool is_composite[MAXN];
int cnt = 0;

void sieve (int n) {
	fill (is_composite, is_composite + n, false);
	for (int i = 2; i < n; ++i) {
		if (!is_composite[i]) prime.push_back (i);
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}

int get(vector<int> &v, int mod){
	int x = 0;
	for (int i=0;i<v.size()-1;i++){
		x = (1000*x+v[i])%mod;
	}
	if (cnt==0) x = (x*1000+v[v.size()-1])%mod;
	else if (cnt==1) x = (x*10+v[v.size()-1])%mod;
	else x = (x*100+v[v.size()-1])%mod;
	return x;
}

void solve()
{
	while(true){
		string s; int l;
		cin >> s >> l;
		if (s=="0"&&l==0) return;
		int ans = -1;
		int n = s.length();
		cnt = n%3;
		vector<int> v((n+2)/3);
		for (int i=0;i<n;i++){
			v[i/3] = (v[i/3]*10+s[i]-48);
		}
		for (int i=0;i<prime.size()&&prime[i]<l;++i){
			int rem = get(v, prime[i]);
			if (rem==0){
				ans = prime[i];
				break;
			}
		}
		if (ans==-1) cout << "GOOD"<<"\n";
		else cout << "BAD"<<" "<< ans << "\n";
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    sieve(MAXN);
    solve();
}