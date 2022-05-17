// Problem: City Attractions
// Contest: Baekjoon Online Judge
// URL: https://www.acmicpc.net/problem/14875
// Memory Limit: 64 MB
// Time Limit: 2000 ms
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

int nxt[2][300001];

void solve()
{
	ll n, k;
	cin >> n >> k;
	vi a(n);
	vector<vi> adj(n);
	vpi f(n, make_pair(-INF, 0)), pf(n, make_pair(-INF, 0));
	for (auto &e : a) cin >> e;
	REP(n - 1) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		adj[u].pb(v), adj[v].pb(u);
	}
	auto dfs1 = y_combinator([&](auto dfs1, int u, int pu) -> void {
		for (auto &v : adj[u]) {
			if (v != pu) {
				dfs1(v, u);
				pii mx = max(make_pair(f[v].fi - 1, f[v].se), make_pair(a[v] - 1, -v));
				ckmax(f[u], mx);
			}
		}
	});
	auto dfs2 = y_combinator([&](auto dfs2, int u, int pu) -> void {
		f[u] = max(f[u], pf[u]);
		pii tmp = {pf[u].fi - 1, pf[u].se};
		ckmax(tmp, make_pair(a[u] - 1, -u));
		for (auto &v : adj[u]) {
			if (v != pu) {
				ckmax(pf[v], tmp);
				ckmax(tmp, max({(pii){a[v] - 2, -v}, {f[v].fi - 2, f[v].se}}));
			}
		}
		reverse(all(adj[u]));
		tmp = {pf[u].fi - 1, pf[u].se};
		ckmax(tmp, make_pair(a[u] - 1, -u));
		for (auto &v : adj[u]) {
			if (v != pu) {
				ckmax(pf[v], tmp);
				ckmax(tmp, max({(pii){a[v] - 2, -v}, {f[v].fi - 2, f[v].se}}));
			}
		}
		for (auto &v : adj[u]) {
			if (v != pu) {
				dfs2(v, u);
			}
		}
	});
	dfs1(0, -1), dfs2(0, -1);
	
	vi nxt(n);
	F0R(i, n) {
		nxt[i] = -f[i].se;
	}
	dbg(nxt);
	int x = nxt[0], y = nxt[nxt[0]];
	int first{};
	while (x != y) {
		x = nxt[x];
		y = nxt[nxt[y]];
	}
	x = 0;
	while (x != y) {
		x = nxt[x];
		y = nxt[y];
	}
	first = x;
	int length{1};
	x = nxt[first];
	while (x != first) {
		length++;
		x = nxt[x];
	}
	x = 0;
	while (k) {
		if (x == first && k >= length) {
			k %= length;
		}else{
			x = nxt[x];
			k--;
		}
	}
	cout << x + 1 << "\n";
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