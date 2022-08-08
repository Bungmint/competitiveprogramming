// Problem: P2 - Patrol
// Contest: DMOJ - APIO '10
// URL: https://dmoj.ca/problem/apio10p2
// Memory Limit: 64 MB
// Time Limit: 600 ms
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

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<vi> adj(n);
	REP(n - 1) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		adj[u].pb(v), adj[v].pb(u);
	}
	vi f(n), g(n);
	auto dfsInit = y_combinator([&](auto self, int u, int pu) -> void {
		ar<int, 2> mx{};
		for (auto &v : adj[u]) {
			if (v != pu) {
				self(v, u);
				ckmax(f[u], 1 + f[v]);
				int ins = 1 + f[v];
				F0R(i, 2) {
					if (ins > mx[i]) swap(ins, mx[i]);
				}
			}
		}
		g[u] = mx[0] + mx[1];
	});
	dfsInit(0, -1);
	if (k == 1) {
		int z = max(*max_element(all(f)), *max_element(all(g)));
		cout << 2 * (n - 1) - z + 1 << "\n";
		return;
	}
	vi a(n), b(n), id(n);
	int d = 0;
	auto dfs = y_combinator([&](auto self, int u, int pu) -> void {
		vi ch;
		a[u] = g[u];
		ar<int, 3> c{0, 0, 0};
		for (auto &v : adj[u]) {
			if (v != pu) {
				self(v, u);
				id[v] = sz(ch);
				ch.pb(a[v]);
				ckmax(a[u], a[v]);
				ckmax(b[u], b[v] + 1);
				int ins = 1 + f[v];
				F0R(i, 3) {
					if (ins > c[i]) swap(ins, c[i]);
				}
			}
		}
		{
			ckmax(b[u], c[0] + c[1] + c[2]);
		}
		if (sz(ch)) {
			vi L(sz(ch)), R(sz(ch));
			FOR(i, 0, sz(ch)) {
				L[i] = ch[i];
				if (i) ckmax(L[i], L[i - 1]);
			}
			ROF(i, 0, sz(ch)) {
				R[i] = ch[i];
				if (i + 1 < sz(ch)) ckmax(R[i], R[i + 1]);
			}
			for (auto &v : adj[u]) {
				if (v != pu) {
					int z = (id[v] ? L[id[v] - 1] : 0);
					if (id[v] + 1 < sz(ch)) ckmax(z, R[id[v] + 1]);
					ckmax(b[u], z + f[v] + 1);
				}
			}
		}
		ckmax(d, a[u]);
		ckmax(d, b[u]);
	});
	dfs(0, -1);
	
	auto dfsF = y_combinator([&](auto self, int u, int pu) -> void {
		ar<int, 4> c{};
		ar<int, 2> cc{};
		int bmax = 0, ii = -1;
		vi ch;
		for (auto &v : adj[u]) {
			if (v != pu) {
				self(v, u);
				ch.pb(f[v] + 1);
				int ins = f[v] + 1;
				F0R(i, 4) {
					if (ins > c[i]) swap(ins, c[i]);
				}
				ins = a[v];
				F0R(i, 2) {
					if (ins > cc[i]) swap(ins, cc[i]);
				}
				if (ckmax(bmax, b[v] + 1)) {
					ii = v;
				}
			}
		}
		ckmax(d, cc[0] + cc[1]);
		ckmax(d, c[0] + c[1] + c[2] + c[3]);
		if (ii != -1) {
			for (auto &v : adj[u]) {
				if (v != pu && v != ii) {
					ckmax(d, bmax + 1 + f[v]);
				}
			}
			bmax = 0;
			int jj = -1;
			for (auto &v : adj[u]) {
				if (v != pu && v != ii) {
					if (ckmax(bmax, 1 + b[v])) {
						jj = v;
					}
				}
			}
			if (jj != -1) ckmax(d, bmax + 1 + f[ii]);
		}
		if (sz(ch)) {
			vi singleL(sz(ch)), singleR(sz(ch)), doubL(sz(ch)), doubR(sz(ch));
			FOR(i, 0, sz(ch)) {
				singleL[i] = ch[i];
				if (i) ckmax(singleL[i], singleL[i - 1]);
			}
			ROF(i, 0, sz(ch)) {
				singleR[i] = ch[i];
				if (i + 1 < sz(ch)) ckmax(singleR[i], singleR[i + 1]);
			}
			FOR(i, 0, sz(ch)) {
				doubL[i] = ch[i] + (i ? singleL[i - 1] : 0);
				if (i) ckmax(doubL[i], doubL[i - 1]);
			}
			ROF(i, 0, sz(ch)) {
				doubR[i] = ch[i] + (i + 1 < sz(ch) ? singleR[i + 1] : 0);
				if (i + 1 < sz(ch)) ckmax(doubR[i], doubR[i + 1]);
			}
			for (auto &v : adj[u]) {
				if (v != pu) {
					int z = (id[v] ? doubL[id[v] - 1] : 0);
					if (id[v] + 1 < sz(ch)) ckmax(z, doubR[id[v] + 1]);
					if (id[v] + 1 < sz(ch) && id[v]) {
						ckmax(z, singleL[id[v] - 1] + singleR[id[v] + 1]);
					}
					ckmax(d, z + a[v]);
				}
			}
		}
	});
	dfsF(0, -1);
	cout << 2 * n - d << "\n";
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