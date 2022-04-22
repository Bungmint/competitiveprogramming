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
int str[N];
struct Node {
	bool isConst;
	int pref, suf, sum, mi;
	Node() {
		isConst = 1;
	}
	Node(int x) {
		isConst = 0;
		pref = max(x, 0);
		suf = max(x, 0);
		sum = x;
		mi = max(0, pref);
	}
	friend Node merge(const Node& a, const Node& b) {
		if (a.isConst) return b;
		if (b.isConst) return a;
		Node res{};
		res.isConst = 0;
		res.pref = max(a.pref, b.pref + a.sum);
		res.suf = max(b.suf, a.suf + b.sum);
		res.sum = a.sum + b.sum;
		res.mi = max(a.pref + b.suf, max(a.mi + b.sum, b.mi + a.sum));
		return res;
	}
}t[N * 4];
int n, q, SZ = 1;

void init() {
	while (SZ < n) SZ *= 2;
}
void build(int x = 0, int l = 0, int r = SZ) {
	if (r - l == 1) {
		if (l < n) t[x] = Node(str[l]);
		return;
	}
	int m = (l + r) >> 1;
	build(2 * x + 1, l, m);
	build(2 * x + 2, m, r);
	t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
}
Node query(int l, int r, int x = 0, int lx = 0, int rx = SZ) {
	if (lx >= r || rx <= l) return Node();
	if (l <= lx && rx <= r) return t[x];
	int m = (lx + rx) >> 1;
	Node a = query(l, r, 2 * x + 1, lx, m);
	Node b = query(l, r, 2 * x + 2, m, rx);
	return merge(a, b);
}

void solve()
{
	cin >> n;
	F0R(i, n) {
		char c;
		cin >> c;
		if (c == 'C') str[i] = -1;
		else str[i] = 1;
	}
	cin >> q;
	init();
	build();
	REP(q) {
		int l, r;
		cin >> l >> r;
		l--;
		Node z = query(l, r);
		cout << z.mi << '\n';
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