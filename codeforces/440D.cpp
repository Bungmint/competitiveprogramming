// Problem: D. Berland Federalization
// Contest: Codeforces - Testing Round #10
// URL: https://codeforces.com/problemset/problem/440/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2022 Youngmin Park. All rights reserved.
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

void setIO(string s) // USACO
{
	#ifndef LOCAL
	    freopen((s + ".in").c_str(), "r", stdin);
	    freopen((s + ".out").c_str(), "w", stdout);
	#endif
}

vi dp[400][401];
bool visvis[400][401];
int subtree[400];


void solve()
{
	int n, k;
	cin >> n >> k;
	vector<vpi> g(n);
	vi par(n);
	F0R(i, n - 1) {
		int u, v;
		cin >> u >> v, u--, v--;
		g[u].pb({v, i}), g[v].pb({u, i});
	}
	auto dfs = y_combinator([&](auto dfs, int u, int pu) -> void {
		subtree[u] = 1;
		for (auto &[v, id] : g[u]) {
			if (v != pu) {
				dfs(v, u);
				par[v] = id;
				vi tmp[401];
				bool vis[401]{};
				FOR(i, 1, k + 1) {
					if (i > subtree[u]) break;
					F0R(j, k + 1) {
						if (j > subtree[v] || i + j > k) break;
						if (!j) {
							if (!vis[i] || sz(tmp[i]) > sz(dp[u][i]) + 1) {
								vis[i] = 1;
								tmp[i] = dp[u][i], tmp[i].pb(id);
							}
						}else{
							if (!vis[i + j] || sz(tmp[i + j]) > sz(dp[u][i]) + sz(dp[v][j])) {
								vis[i + j] = 1;
								tmp[i + j] = dp[u][i];
								tmp[i + j].insert(tmp[i + j].end(), all(dp[v][j]));
							}
						}
					}
				}
				subtree[u] += subtree[v];
				FOR(i, 1, k + 1) {
					if (i > subtree[u]) break;
					visvis[u][i] = vis[i];
					dbg(u, i, tmp[i]);
					dp[u][i] = tmp[i];
				}
				
			}
		}
	});
	dfs(0, -1);
	int root = 0;
	int ans = INF;
	F0R(i, n) {
		if (!visvis[i][k]) continue;
		if (i == 0) {
			ckmin(ans, sz(dp[i][k]));
		}else{
			if (ckmin(ans, sz(dp[i][k]) + 1)) {
				root = i;
			}
		}
	}
	vi res = dp[root][k];
	if (root) res.pb(par[root]);
	cout << sz(res) << "\n";
	for (auto &e : res) cout << e + 1 << " ";
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