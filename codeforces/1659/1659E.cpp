// Problem: AND-MEX Walk
// Contest: Codeforces
// URL: https://m1.codeforces.com/contest/1659/problem/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2022 Youngmin Park. All rights reserved.
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
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

const int N = 1e5;
vpi adj[N];
bool vis[N];

struct DSU {
	vi par, sz;
	vector<bool> good;
	void init(int n) {
		par.resize(n), iota(all(par), 0);
		sz.assign(n, 1);
		good.resize(n);
	}
	int get(int u) {return u == par[u] ? u : par[u] = get(par[u]);}
	void unite(int u, int v) {
		u = get(u), v = get(v);
		if (u == v) return;
		if (sz[u] > sz[v]) swap(u, v);
		sz[v] += sz[u];
		par[u] = v;
		good[u] = good[u] || good[v];
	}
}dsu[31];

DSU safe;

void solve()
{
	int n, m;
	cin >> n >> m;
	REP(m) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		adj[u].pb({v, w});
		adj[v].pb({u, w});
	}
	F0R(i, 31) dsu[i].init(n);
	// queue<int> q;
	F0R(u, n) {
		for (auto &[v, w] : adj[u]) {
			ROF(j, 0, 30) {
				if ((1 << j) & w) {
					dsu[j].unite(u, v);
				}
				if (w & 1) continue;
			}
			if (w == 0) dsu[30].unite(u, v);
		}
	}
	F0R(u, n) {
		for (auto &[v, w] : adj[u]) {
			if (w & 1) continue;
			ROF(j, 0, 31) {
				dsu[j].good[dsu[j].get(u)] = 1;
			}
		}
	}
	int q;
	cin >> q;
	REP(q) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		int ans = 2;
		FOR(i, 0, 30) {
			int z = dsu[i].get(u), w = dsu[i].get(v);
			if (z == w) {
				ckmin(ans, 0);
				break;
			}
		}
		FOR(i, 1, 31) {
			int z = dsu[i].get(u);
			if (dsu[i].good[z]) {
				ckmin(ans, 1);
				break;
			}
		}
		
		cout << ans << '\n';
	}
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