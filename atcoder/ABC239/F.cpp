// Problem: F - Construct Highway
// Contest: AtCoder - Denso Create Programming Contest 2022(AtCoder Beginner Contest 239)
// URL: https://atcoder.jp/contests/abc239/tasks/abc239_f
// Memory Limit: 1024 MB
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

// From the USACO tutorial lol
struct DSU {
	vector<int> par;
	vector<vi> todo;
	DSU(int N) { par.resize(N), iota(all(par), 0); todo.assign(N, {});}

	// get representive component (uses path compression)
	// To use rollback, disable path compression
	int get(int x) { return par[x] == x ? x : par[x] = get(par[x]); }
	
	bool same_set(int a, int b) { return get(a) == get(b); }
	
	int size(int x) { return sz(todo[x]); }
	
	bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return false;
		if (size(x)<size(y)) swap(x, y);
		while(sz(todo[y])) todo[x].pb(todo[y].back()), todo[y].pop_back();
		par[y] = x;
		return true;
	}
};

void solve()
{
	int n, m, cc = 0;
	cin >> n >> m;
	vi d(n), comp(n);
	vector<vi> g(n);
	vector<bool> vis(n);
	bool cycle = 0;
	for (auto &e: d) cin >> e;
	REP(m){
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].pb(v), g[v].pb(u);
	}
	auto dfsInit = y_combinator([&](auto dfsInit, int u, int pu, int ccc)->void{
		vis[u] = 1;
		comp[u] = ccc;
		for (auto &e: g[u]){
			if (!vis[e]) dfsInit(e, u, ccc);
			else if (e != pu){
				cycle = 1;
			}
		}
	});
	F0R(i, n){
		if (!vis[i]){
			dfsInit(i, -1, cc++);
			if (cycle){
				cout << -1;
				return;
			}
		}
	}
	int totEdge = 0;
	vi req(n);
	F0R(i, n){
		if (d[i]<sz(g[i])){
			cout << -1;
			return;
		}
		totEdge += -sz(g[i]) + d[i];
		req[i] = -sz(g[i]) + d[i];
	}
	dbg(totEdge);
	if (totEdge!=2*(n-m-1)){
		cout << -1;
		return;
	}
	DSU dsu(cc);
	F0R(i, n){
		REP(req[i]) dsu.todo[comp[i]].pb(i);
	}
	set<pii> todo;
	F0R(i, cc){
		if (sz(dsu.todo[i])) todo.insert({sz(dsu.todo[i]), i});
	}
	vpi ans;
	while(sz(todo)){
		dbg(todo);
		dbg(dsu.todo);
		if (sz(todo)==1){
			cout << -1;
			return;
		}
		auto [sz1, id1] = *--todo.end();
		todo.erase(--todo.end());
		auto [sz2, id2] = *--todo.end();
		todo.erase(--todo.end());
		int u = dsu.todo[id1].back(), v = dsu.todo[id2].back();
		dsu.todo[id1].pop_back(), dsu.todo[id2].pop_back();
		dsu.unite(id1, id2);
		int resId = (sz1 >= sz2 ? id1 : id2);
		if (sz(dsu.todo[resId])) todo.insert({sz(dsu.todo[resId]), resId});
		ans.pb({u, v});
	}
	for (auto &[x, y]: ans) cout << x+1 << " " << y+1 << "\n";
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