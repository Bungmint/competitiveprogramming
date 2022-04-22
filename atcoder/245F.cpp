// Problem: F - Endless Walk
// Contest: AtCoder - AtCoder Beginner Contest 245
// URL: https://atcoder.jp/contests/abc245/tasks/abc245_f
// Memory Limit: 1024 MB
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

const int N = 2e5;
vi adj[N], radj[N], cond[N], group[N];
int head[N], cnt[N];
bool vis1[N], vis2[N], vis3[N], isHead[N], good[N];
vi topsort, comp, tt;
int n, m;

void dfs1(int u) {
	vis1[u] = 1;
	for (auto &e : adj[u]) if (!vis1[e]) dfs1(e);
	topsort.pb(u);
}
void dfs2(int u) {
	vis2[u] = 1;
	comp.pb(u);
	for (auto &e : radj[u]) {
		if (!vis2[e]) dfs2(e);
	}
}
void dfs3(int u) {
	vis3[u] = 1;
	for (auto &e : cond[u]) if (!vis3[e]) dfs3(e);
	tt.pb(u);
}

void solve()
{
	cin >> n >> m;
	REP(m) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		adj[u].pb(v);
		radj[v].pb(u);
	}
	F0R(i, n) {
		if (!vis1[i]) dfs1(i);
	}
	reverse(all(topsort));
	for (auto &u : topsort) {
		if (!vis2[u]) {
			comp.clear();
			dfs2(u);
			for (auto &e : comp) head[e] = u, cnt[u]++, group[u].pb(e);
			isHead[u] = 1;
			if (cnt[u] > 1) good[u] = 1;
		}
	}
	set<pii> edges;
	F0R(i, n) {
		for (auto &j : adj[i]) {
			if (head[i] != head[j] && !edges.count({head[i], head[j]})) {
				cond[head[i]].pb(head[j]);
				edges.insert({head[i], head[j]});
			}
		}
	}
	F0R(i, n) {
		if (isHead[i] && !vis3[i]) {
			dfs3(i);
		}
	}
	int ans{};
	for (auto &e : tt) {
		for (auto &nxt : cond[e]) {
			good[e] |= good[nxt];
		}
		if (good[e]) ans += cnt[e];
	}
	cout << ans;
	
	
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