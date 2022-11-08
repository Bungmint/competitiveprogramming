// Problem: Hotel Queries
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1143
// Memory Limit: 512 MB
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

struct SegTree {
	int sz;
	vi t;
	SegTree(int n) {
		sz = 1;
		while (sz < n) sz *= 2;
		t.assign(sz * 2, 0);
	}
	void build(int x, int l, int r, vi& a) {
		if (r - l == 1) {
			if (l < sz(a)) t[x] = a[l];
			return;
		}
		int m = (l + r) >> 1;
		build(2 * x + 1, l, m, a);
		build(2 * x + 2, m, r, a);
		t[x] = max(t[2 * x + 1], t[2 * x + 2]);
	}
	void build(vi &a) {
		build(0, 0, sz, a);
	}
	void upd(int i, int v, int x, int l, int r) {
		if (r - l == 1) {
			t[x] += v;
			return;
		}
		int m = (l + r) >> 1;
		if (i < m) upd(i, v, 2 * x + 1, l, m);
		else upd(i, v, 2 * x + 2, m, r);
		t[x] = max(t[2 * x + 1], t[2 * x + 2]);
	}
	void upd(int i, int v) {
		upd(i, v, 0, 0, sz);
	}
	int go(int v, int x, int l, int r) {
		if (t[x] < v) return -1;
		if (r - l == 1) {
			return l;
		}
		int m = (l + r) >> 1;
		if (t[2 * x + 1] >= v) return go(v, 2 * x + 1, l, m);
		else return go(v, 2 * x + 2, m, r);
	}
	int go(int v) {
		return go(v, 0, 0, sz);
	}
};


void solve()
{
	int n, m;
	cin >> n >> m;
	vi h(n);
	for (auto &e : h) cin >> e;
	SegTree st(n);
	st.build(h);
	REP(m) {
		int x;
		cin >> x;
		int z = st.go(x);
		cout << z + 1 << ' ';
		if (z != -1) st.upd(z, -x);
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