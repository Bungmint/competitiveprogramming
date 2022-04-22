// Problem: Problem 3. Seating
// Contest: USACO - USACO 2013 January Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=231
// Memory Limit: 256 MB
// Time Limit: 4000 ms
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

const int N = 5e5;
int n, m;
int lazy[6 * N];
int SZ;

struct Node {
	int pref, suf, max, len;
	Node(int p = 0, int s = 0, int m = 0, int l = 0) : pref(p), suf(s), max(m), len(l) {}
}t[4 * N];

void init() {
	SZ = 1;
	while (SZ < n) SZ *= 2;
	memset(lazy, -1, sizeof(lazy));
}
Node merge(const Node& a, const Node& b) {
	Node res;
	res.max = max({a.max, b.max, a.suf + b.pref});
	res.pref = a.pref;
	res.len = a.len + b.len;
	res.suf = b.suf;
	if (a.pref == a.len) res.pref += b.pref;
	if (b.suf == b.len) res.suf += a.suf;
	return res;
}
void clear(int x, int fl) {
	t[x].pref = t[x].suf = t[x].max = t[x].len * fl;
}
void push(int x) {
	if (lazy[x] == -1) return;
	clear(x, lazy[x]);
	lazy[2 * x + 1] = lazy[2 * x + 2] = lazy[x];
	lazy[x] = -1;
}
void build(int x, int l, int r) {
	if (r - l == 1) {
		if (l < n) t[x] = Node(1, 1, 1, 1);
		return;
	}
	int m = (l + r) / 2;
	build(2 * x + 1, l, m); build(2 * x + 2, m, r);
	t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
}
void upd(int l, int r, int v, int x, int lx, int rx) {
	push(x);
	if (lx >= r || rx <= l) return;
	if (l <= lx && rx <= r) {
		lazy[x] = v;
		push(x);
		return;
	}
	int m = (lx + rx) >> 1;
	upd(l, r, v, 2 * x + 1, lx, m);
	upd(l, r, v, 2 * x + 2, m, rx);
	t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
}
int query(int p, int x, int l, int r) {
	push(x);
	if (t[x].max < p) return -1;
	if (r - l == 1) {
		return l;
	}
	push(2 * x + 1);
	push(2 * x + 2);
	int m = (l + r) >> 1;
	if (t[2 * x + 1].max >= p) return query(p, 2 * x + 1, l, m);
	else if (t[2 * x + 1].suf + t[2 * x + 2].pref >= p) {
		return m - t[2 * x + 1].suf;
	}
	else return query(p, 2 * x + 2, m, r);
}




void solve()
{
	cin >> n >> m;
	init();
	build(0, 0, SZ);
	int ans = 0;
	REP(m) {
		char t;
		cin >> t;
		if (t == 'A') {
			int x;
			cin >> x;
			int z = query(x, 0, 0, SZ);
			if (z == -1) ans++;
			else upd(z, z + x, 0, 0, 0, SZ);
			dbg(z);
		}else {
			int l, r;
			cin >> l >> r;
			l--;
			upd(l, r, 1, 0, 0, SZ);
		}
		dbg(ans);
	}
	cout << ans << '\n';
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    setIO("seating");
    while (testcase--)
    {
        solve();
    }
}