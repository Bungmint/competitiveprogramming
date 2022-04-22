// Problem: D. Wizard's Tour
// Contest: Codeforces - Codeforces Round #434 (Div. 1, based on Technocup 2018 Elimination Round 1)
// URL: https://codeforces.com/contest/860/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2021 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
using ld = long double;
template <typename T, size_t SZ>
using ar = array<T, SZ>;

#define all(v) (v).begin(), (v).end()
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define REP(a) F0R(_, a)

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v)
{
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}
void dbg_out()
{
    cerr << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

inline namespace RecursiveLambda{
	template <typename Fun>
	struct y_combinator_result{
		Fun fun_;
		template <typename T> 
		explicit y_combinator_result(T &&fun): fun_(forward<T>(fun)){}
		template <typename...Args>
		decltype(auto) operator()(Args &&...args){
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun){
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<vpi> g(n);
	vector<vi> tmp(n);
	vector<bool> vis(n);
	vector<ar<int, 3>> ans;
	vi depth(n);
	F0R(id, m){
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].pb({v, id}), g[v].pb({u, id});
	}
	
	auto dfs = y_combinator([&](auto dfs, int u, int pu)->void{
		vis[u] = 1;
		for (auto &[v, id]: g[u]){
			if (v==pu) continue;
			if (vis[v]){
				if (depth[u] > depth[v]){
					tmp[u].pb(v);
				}
			}else{
				depth[v] = depth[u] + 1;
				dfs(v, u);
				if (sz(tmp[v])){
					ans.pb({u, v, tmp[v].back()});
					tmp[v].pop_back();
					assert(tmp[v].empty());
				}else{
					tmp[u].pb(v);
				}
			}
			while(sz(tmp[u])>=2){
				int v = tmp[u].back();
				tmp[u].pop_back();
				int w = tmp[u].back();
				tmp[u].pop_back();
				ans.pb({v, u, w});
			}
		}
	});
	F0R(i, n){
		if (!vis[i]){
			dfs(i, -1);
		}
	}
	cout << sz(ans) << "\n";
	for (auto &[i, j, k]: ans) cout << i+1 << ' ' << j+1 << ' ' << k+1 << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}