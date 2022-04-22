// Problem: C. Serge and Dining Room
// Contest: Codeforces - Codeforces Round #569 (Div. 1)
// URL: https://codeforces.com/contest/1179/problem/C
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



template<typename T, typename Merge = plus<T>>
struct SegTree{
	int sz;
	const Merge merge;
	vector<T> t;
	SegTree(int n) : merge(Merge()) {
		sz = 1;
		while (sz<n) sz*=2;
		t.resize(sz*2);
	}
	void build(int vec[], int n, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        if (l < n)
	            t[x] = T(vec[l]);
	        return;
	    }
	    int mid = (l + r) / 2;
	    build(vec, n, 2 * x + 1, l, mid);
	    build(vec, n, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void build(int vec[], int n)
	{
	    build(vec, n, 0, 0, sz);
	}
	void upd(int i, const T& v, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        t[x] = v;
	        return;
	    }
	    int mid = (l + r) / 2;
	    if (i < mid)
	        upd(i, v, 2 * x + 1, l, mid);
	    else
	        upd(i, v, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void upd(int i, const T& v)
	{
	    upd(i, v, 0, 0, sz);
	}
	int query(int x, int lx, int rx, int cumneg)
	{
	    if (t[x].pos <= cumneg) return -1;
	    if (rx - lx == 1) return lx;
	    int mid = (lx + rx) / 2;
	   	if (t[2 * x + 2].pos > cumneg) return query(2 * x + 2, mid, rx, cumneg);
	   	else return query(2 * x + 1, lx, mid, cumneg - t[2 * x + 2].pos + t[2 * x + 2].neg);
	}
	int query()
	{
	    return query(0, 0, sz, 0);
	}
};

const int N = 3e5 + 100;
vi tmp;
int c[3 * N];
int getComp(int x) {
	return lb(all(tmp), x) - begin(tmp);
}

struct Node {
	int pos, neg;
	Node(int x = 0) {
		pos = neg = 0;
		if (x > 0) pos = x;
		else neg = -x;
	}
	Node operator+ (const Node& other) const {
		Node res{};
		res.pos = other.pos;
		res.neg = neg;
		if (pos > other.neg) res.pos += pos - other.neg;
		else res.neg += other.neg - pos;
		return res;
	}
};


void solve()
{
	int n, m, q;
	cin >> n >> m;
	vi a(n), b(m);
	for (auto &e : a) cin >> e, tmp.pb(e);
	for (auto &e : b) cin >> e, tmp.pb(e);
	cin >> q;
	vector<ar<int, 3>> query(q);
	for (auto &[t, i, x] : query) cin >> t >> i >> x, i--, tmp.pb(x);
	sort(all(tmp)), tmp.resize(unique(all(tmp)) - tmp.begin());
	dbg(tmp);
	SegTree<Node> st(sz(tmp));
	for (auto &e : a) {
		e = getComp(e);
		c[e]++;
		dbg(e, c[e]);
	}
	for (auto &e : b) {
		e = getComp(e);
		c[e]--;
	}
	st.build(c, sz(tmp));
	for (auto &[t, i, x] : query) {
		x = getComp(x);
		if (t == 1) {
			dbg(a[i], x, c[a[i]]);
			c[a[i]]--;
			Node r = Node(c[a[i]]);
			dbg(r.pos, r.neg);
			st.upd(a[i], r);
			a[i] = x;
			c[a[i]]++;
			r = Node(c[a[i]]);
			st.upd(a[i], r);
		}else{
			c[b[i]]++;
			Node r = Node(c[b[i]]);
			st.upd(b[i], r);
			b[i] = x;
			c[b[i]]--;
			r = Node(c[b[i]]);
			st.upd(b[i], r);
		}
		int z = st.query();
		cout << (z == -1 ? z : tmp[z]) << '\n';
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