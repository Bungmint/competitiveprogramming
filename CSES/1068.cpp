#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpi = vector<pii>;
using vpl = vector<pll>;
using ld = long double;

#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define pb push_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, b) FOR(i, 0, b)
#define ROF(i, a, b) for (int i = (b)-1; i >= a; i--)
#define R0F(i, b) ROF(i, 0, b)
#define REP(a) F0R(_, a)

const int INF = 1e9;
const ll LINF = 1e18;


template<typename T, typename...Us>
void re(T&& t, Us&&...u){
	cin >> forward<T>(t);
	(int[]){(cin >> forward<Us>(u), 0)...};
}
template<typename T, typename...Us>
void pr(T&& t, Us&&...u){
	cout << forward<T>(t);
	(int[]){(cout<<" "<<forward<Us>(u), 0)...};
	cout << "\n";
}

void setIO(const string&s){
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	if (sz(s)){
		freopen((s+".in").c_str(), "r", stdin);
		freopen((s+".out").c_str(), "w", stdout);
	}
}


void solve(){
	ll n;
	re(n);
	vl a;
	while(true){
		a.pb(n);
		if (n==1) break;
		if (n&1) (n*=3)+=1;
		else n/=2;
	}
	for (auto&e:a) cout << e << " ";
}

int main(){
	setIO("");
	solve();
}