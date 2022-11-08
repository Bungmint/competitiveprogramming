// Problem: Problem 2. Marathon
// Contest: USACO - USACO 2014 December Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=495
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

const int N = 1e5;
pii p[N];
int n, q;
int SZ;

struct Node {
	int tot, sh, len;
	ar<int, 2> pref{}, suf{};
	Node() {
		tot = sh = 2 * INF;
		len = 0;
		pref = suf = {-1, -1};
	}
	Node(int x) {
		tot = sh = 0;
		len = 1;
		pref = {x, -1};
		suf = {-1, x};
	}
}t[6 * N];

int dist(int i, int j) {
	return abs(p[i].fi - p[j].fi) + abs(p[i].se - p[j].se);
}
Node merge(const Node& a, const Node& b) {
	if (a.len == 0) return b;
	if (b.len == 0) return a;
	Node res = Node();
	res.tot = a.tot + b.tot + dist(a.suf[1], b.pref[0]);
	res.sh = min(a.sh + b.tot, b.sh + a.tot) + dist(a.suf[1], b.pref[0]);
	if (a.len > 1) {
		ckmin(res.sh, dist(a.suf[0], b.pref[0]) + a.tot + b.tot - dist(a.suf[0], a.suf[1]));
	}
	if (b.len > 1) {
		ckmin(res.sh, dist(a.suf[1], b.pref[1]) + a.tot + b.tot - dist(b.pref[0], b.pref[1]));
	}
	res.len = a.len + b.len;
	res.pref = a.pref;
	if (a.pref[1] == -1) res.pref[1] = b.pref[0];
	res.suf = b.suf;
	if (b.suf[0] == -1) res.suf[0] = a.suf[1];
	return res;
}
void init() {
	SZ = 1;
	while (SZ < n) SZ *= 2;
}
void build(int x, int l, int r) {
	if (r - l == 1) {
		if (l < n) t[x] = Node(l);
		return;
	}
	int m = (l + r) >> 1;
	build(2 * x + 1, l, m);
	build(2 * x + 2, m, r);
	t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
}
void upd(int i, Node v, int x, int l, int r) {
	if (r - l == 1) {
		t[x] = v;
		return;
	}
	int m = (l + r) >> 1;
	if (i < m) upd(i, v, 2 * x + 1, l, m);
	else upd(i, v, 2 * x + 2, m, r);
	t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
}
Node query(int l, int r, int x, int lx, int rx) {
	dbg(l, r, lx, rx, x);
	if (rx <= l || r <= lx) return Node();
	if (l <= lx && rx <= r) return t[x];
	int m = (lx + rx) >> 1;
	Node a = query(l, r, 2 * x + 1, lx, m);
	Node b = query(l, r, 2 * x + 2, m, rx);
	return merge(a, b);
}





void solve()
{
	cin >> n >> q;
	F0R(i, n) cin >> p[i].fi >> p[i].se;
	init();
	build(0, 0, SZ);
	REP(q) {
		char c;
		cin >> c;
		if (c == 'Q') {
			int i, j;
			cin >> i >> j;
			i--;
			Node res = query(i, j, 0, 0, SZ);
			cout << res.sh << '\n';
		}else {
			int i, x, y;
			cin >> i >> x >> y;
			i--;
			p[i] = {x, y};
			Node res = Node(i);
			upd(i, res, 0, 0, SZ);
		}
	}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    setIO("marathon");
    while (testcase--)
    {
        solve();
    }
}