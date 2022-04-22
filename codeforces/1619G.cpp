// Problem: G. Unusual Minesweeper
// Contest: Codeforces - Codeforces Round #762 (Div. 3)
// URL: https://codeforces.com/contest/1619/problem/G
// Memory Limit: 256 MB
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

struct DSU {
	vi par, sz, t;
	DSU(int n) {
		sz.assign(n, 1);
		t.assign(n, 2 * INF);
		par.resize(n);
		iota(all(par), 0);
	}
	int get(int x) {
		return x == par[x] ? x : par[x] = get(par[x]);
	}
	void unite(int x, int y) {
		x = get(x), y = get(y);
		if (x == y) return;
		if (sz[x] < sz[y]) swap(x, y);
		sz[x] += sz[y];
		par[y] = x;
		ckmin(t[x], t[y]);
	}
};

struct Bomb {
	int x, y, t;
};

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<Bomb> a(n);
	DSU dsu(n);
	vi xs, ys;
	F0R(i, n) {
		cin >> a[i].x >> a[i].y >> a[i].t;
		dsu.t[i] = a[i].t;
		xs.pb(a[i].x);
		ys.pb(a[i].y);
	}
	sort(all(xs)), xs.resize(unique(all(xs)) - xs.begin());
	sort(all(ys)), ys.resize(unique(all(ys)) - ys.begin());
	vector<vpi> xx(sz(xs)), yy(sz(ys));
	F0R(i, n) {
		auto &[x, y, t] = a[i];
		x = lb(all(xs), x) - xs.begin();
		y = lb(all(ys), y) - ys.begin();
		xx[x].pb({y, i});
		yy[y].pb({x, i});
	}
	for (auto &v : xx) sort(all(v));
	for (auto &v : yy) sort(all(v));
	F0R(i, n) {
		auto &[x, y, t] = a[i];
		int it = ub(all(xx[x]), make_pair(y, i)) - xx[x].begin();
		if (it < sz(xx[x]) && abs(ys[xx[x][it].fi] - ys[y]) <= k) {
			dsu.unite(i, xx[x][it].se);
		}
		it -= 2;
		if (it >= 0 && abs(ys[xx[x][it].fi] - ys[y]) <= k) {
			dsu.unite(i, xx[x][it].se);
		}
		
		it = ub(all(yy[y]), make_pair(x, i)) - yy[y].begin();
		if (it < sz(yy[y]) && abs(xs[yy[y][it].fi] - xs[x]) <= k) {
			dsu.unite(i, yy[y][it].se);
		}
		it -= 2;
		if (it >= 0 && abs(xs[yy[y][it].fi] - xs[x]) <= k) {
			dbg(i, yy[y][it].se, it);
			dsu.unite(i, yy[y][it].se);
		}
	}
	dbg(dsu.sz);
	set<pii> st;
	F0R(i, n) {
		int x = dsu.get(i);
		int cnt = dsu.t[x];
		if (st.count({cnt, x})) continue;
		st.insert({cnt, x});
	}
	int cur = -1;
	while (sz(st)) {
		cur++;
		while (sz(st) && st.begin()->fi <= cur) st.erase(st.begin());
		if (st.empty()) break;
		st.erase(--st.end());
	}
	cout << cur << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}