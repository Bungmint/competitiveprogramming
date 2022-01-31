#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <cassert>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
#define pb push_back
#define fi first
#define second se
#define lb lower_bound
#define FOR(i, a, b) for (int i = (a);i<(b);++i)
#define F0R(i, b) FOR(i, 0, b)
#define sz(x) (int)(x).size()

const int MN = 1e6;
const int MOD = 1e9+7;
int f[MN+1], mu[MN+1], g[MN+1];
unordered_map<int,int> mp;
vi pr;
int norm(int x){return (x<0? x+MOD:x);}
void _norm(int& x){x = (x<0? x+MOD:x);}
inline int add(int a, int b){return ((ll)a+(ll)b)%MOD;}
inline int mul(int a, int b){return ((ll)a*(ll)b)%MOD;}
inline int sub(int a, int b){return norm((ll)(a-b)%MOD);}
void _add(int&a, const int& b){a +=b, a%=MOD;}
void _mul(int&a, const int&b){a = ((ll)a*(ll)b)%MOD;}
void _sub(int&a, const int&b){a = ((ll)a-(ll)b+MOD)%MOD;}
int bin_pow(int x, int p){
	int res = 1;
	while(p){
		if (p&1) _mul(res, x);
		p/=2;
		x = mul(x, x);
	}
	return res;
}
int DIV= bin_pow(3, MOD-2);
int _div(int a, int b){return mul(a, bin_pow(b, MOD-2));}
void linsieve(){
	fill(mu, mu+MN+1, 2);
	mu[1] = 1;
	for (int i=2;i<=MN;++i){
		if (mu[i]==2) mu[i] = -1, pr.pb(i);
		for (int j=0;j<sz(pr)&&pr[j]*i<=MN;++j){
			if (i%pr[j]==0){
				mu[i*pr[j]] = 0;
				break;
			}else mu[i*pr[j]] = -mu[i];
		}
	}
	for (ll i=1;i<=MN;++i){
		g[i] = (i*i-3LL*i+2LL)%MOD;
		assert(g[i]>=0);
	}
	for (int d = 1;d<=MN;++d){
		for (int j=1;j*d<=MN;++j){
			f[j*d] += mu[d]*g[j];
			f[j*d]%=MOD;_norm(f[j*d]);
		}
	}
	for (int i=1;i<=MN;++i){
		_add(f[i], f[i-1]);
	}
}
int calc(int x){
	if (x<=MN) return f[x];
	if (mp.count(x)) return mp[x];
	int v = ((ll)bin_pow(x, 3)-(ll)3*bin_pow(x,2) + (ll)2*x)%MOD;
	v = mul(v+MOD, DIV);
	for (int i=2, la;i<=x;i = la+1){
		la = x/(x/i);
		_sub(v, mul(calc(x/i), la-i+1));
	}
	return mp[x] = v;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	// cin.exceptions(cin.failbit);
	mp.reserve(1024), mp.max_load_factor(0.25);
	linsieve();
	int tc;
	cin >> tc;
	while(tc--){
		int n;
		cin >> n;
		cout << calc(n)<<"\n";
	}
	return 0;
}