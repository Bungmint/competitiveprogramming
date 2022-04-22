// Problem: E. Domino Principle
// Contest: Codeforces - Codeforces Beta Round #52 (Div. 2)
// URL: https://codeforces.com/contest/56/problem/E
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
const int ID = 0;
int lazy[N << 2], t[N << 2];
int SZ = 1;
int n;
void init() {
	while (SZ < n) SZ *= 2;
}
void push(int x, int l, int r) {
	if (lazy[x] == 0) return;
	t[x] += lazy[x];
	if (r - l > 1) {
		lazy[2 * x + 1] += lazy[x];
		lazy[2 * x + 2] += lazy[x];
	}
	lazy[x] = 0;
}
int merge(int a, int b) {return max(a, b);}
void upd(int i, int v, int x = 0, int lx = 0, int rx = SZ) {
	push(x, lx, rx);
	if (rx - lx == 1) {
		t[x] = merge(t[x], v);
		return;
	}
	int m = (lx + rx) >> 1;
	if (i < m) upd(i, v, 2 * x + 1, lx, m);
	else upd(i, v, 2 * x + 2, m, rx);
	t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
}
void range_upd(int l, int r, int v, int x = 0, int lx = 0, int rx = SZ) {
	push(x, lx, rx);
	if (rx <= l || lx >= r) return;
	if (l <= lx && rx <= r) {
		lazy[x] += v;
		push(x, lx, rx);
		return;
	}
	int m = (lx + rx) >> 1;
	range_upd(l, r, v, 2 * x + 1, lx, m);
	range_upd(l, r, v, 2 * x + 2, m, rx);
	t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
}
int query(int l, int r, int x = 0, int lx = 0, int rx = SZ) {
	push(x, lx, rx);
	if (rx <= l || lx >= r) return ID;
	if (l <= lx && rx <= r) {
		return t[x];
	}
	int m = (lx + rx) >> 1;
	int a = query(l, r, 2 * x + 1, lx, m);
	int b = query(l, r, 2 * x + 2, m, rx);
	return merge(a, b);
}

void solve()
{
	cin >> n;
	vi x(n), h(n), id(n), ans(n), xs;
	F0R(i, n) cin >> x[i] >> h[i], xs.pb(x[i]);
	sort(all(xs));
	iota(all(id), 0);
	sort(all(id), [&](auto p, auto q) {
		return x[p] < x[q];
	});
	init();
	auto get = [&](int xx) {
		return ub(all(xs), xx) - xs.begin() - 1;
	};
	R0F(i, n) {
		int cur = id[i];
		int L = get(x[cur] + 1);
		int R = get(x[cur] + h[cur] - 1);
		dbg(L, R);
		range_upd(i, n, 1);
		ans[cur] = query(L, R + 1);
		upd(i, ans[cur]);
	}
	F0R(i, n) cout << ans[i] << ' ';
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