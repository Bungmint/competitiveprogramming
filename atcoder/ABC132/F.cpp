// Problem: F - Small Products
// Contest: AtCoder - AtCoder Beginner Contest 132
// URL: https://atcoder.jp/contests/abc132/tasks/abc132_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
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

void add_(int& a, const int b) {
	a += b;
	if (a >= MOD) a -= MOD;
}
int mul(int a, int b) {
	return 1LL * a * b % MOD;
}

struct Fenwick {
	vector<int> t;
	int n;
	Fenwick(int n_, int x) : t(vi(n_ + 1, x)), n(n_) {}
	void upd(int i, int v) {
		for (++i; i <= n; i += i & -i) add_(t[i], v);
	}
	int query(int i) {
		int res = 0;
		for (++i; i > 0; i -= i & -i) add_(res, t[i]);
		return res;
	}
	void clear() {
		fill(all(t), 0);
	}
};

#define prev preapiofjewopfj

void solve()
{
	int n, k;
	cin >> n >> k;
	vi order, a;
	for (int l = 1; l <= n; ) {
		int cur = n / l;
		int r = n / cur;
		order.pb(l);
		a.pb(cur);
		l = r + 1;
	}
	Fenwick fen(sz(order), 0), prev(sz(order), 0);
	vi dp(sz(order)), pre(sz(order)), cov(sz(order));
	F0R(i, sz(order)) {
		int x = a[i];
		int id = ub(all(order), x) - order.begin();
		int nxt = (id == sz(order) ? n + 1 : order[id]);
		if (x == nxt - 1) {
			cov[i] = id - 1;
		}else cov[i] = id - 2;
	}
	FOR(i, 1, k) {
		if (i == 1) {
			F0R(i, sz(order)) {
				dp[i] = a[i];
				int nxt = (i + 1 == sz(order) ? n + 1 : order[i + 1]);
				fen.upd(i, mul(nxt - order[i], dp[i]));
			}
		}else{
			F0R(i, sz(order)) {
				int cur = order[i];
				int nxt = (i + 1 == sz(order) ? n + 1 : order[i + 1]);
				int q = prev.query(cov[i]);
				int t = (cov[i] + 1 == sz(order) ? n + 1 : order[cov[i] + 1]);
				if (t - 1 < a[i]) add_(q, mul(dp[cov[i] + 1], a[i] - t + 1));
				dp[i] = q;
				fen.upd(i, mul(nxt - order[i], dp[i]));
			}
		}
		prev.t = fen.t;
		pre = dp;
		fill(all(dp), 0);
		fen.clear();
	}
	cout << prev.query(sz(order) - 1);
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