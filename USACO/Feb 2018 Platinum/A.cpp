// Problem: Problem 1. Slingshot
// Contest: USACO - USACO 2018 February Contest, Platinum
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=816
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

#define int long long
template<typename T, typename Merge = plus<T>>
struct SegTree{
	int sz;
	const Merge merge;
	vector<T> t;
	SegTree(int n) : merge(Merge()) {
		sz = 1;
		while (sz<n) sz*=2;
		t.assign(sz*2, LINF);
	}
	void build(vector<T> &vec, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        if (l < (int)vec.size())
	            t[x] = vec[l];
	        return;
	    }
	    int mid = (l + r) / 2;
	    build(vec, 2 * x + 1, l, mid);
	    build(vec, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void build(vector<T> &vec)
	{
	    build(vec, 0, 0, sz);
	}
	void upd(int i, const T& v, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        t[x] = merge(t[x], v);
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
	T query(int l, int r, int x, int lx, int rx)
	{
	    if (lx >= r || rx <= l)
	        return 2 * LINF;
	    if (lx >= l && rx <= r)
	        return t[x];
	    int mid = (lx + rx) / 2;
	    T a = query(l, r, 2 * x + 1, lx, mid);
	    T b = query(l, r, 2 * x + 2, mid, rx);
	    return merge(a, b);
	}
	T query(int l, int r)
	{
	    return query(l, r, 0, 0, sz);
	}
	void clear() {
		t.assign(sz*2, 2 * LINF);
	}
};

struct Min {
	int operator()(const int& a, const int& b) const {
		return min(a, b);
	}
};


vi ind;
int getComp(int x) {
	return lb(all(ind), x) - ind.begin();
}
void insert(int x) {
	ind.pb(x);
}


void solve()
{
	int n, q;
	cin >> n >> q;
	vector<ar<int, 3>> query;
	vl ans(q + 1);
	F0R(i, n) {
		int x, y, t;
		cin >> x >> y >> t;
		insert(y);
		query.pb({x, -t, y});
	}
	FOR(i, 1, 1 + q) {
		int a, b;
		cin >> a >> b;
		insert(b);
		query.pb({a, i, b});
		ans[i] = abs(b - a);
	}
	sort(all(query));
	sort(all(ind));
	ind.resize(unique(all(ind)) - ind.begin());
	SegTree<int, Min> st(sz(ind));
	for (auto &[x, t, y] : query) {
		y = getComp(y);
		if (t <= 0) {
			st.upd(y, -t - x - ind[y]);
		}else {
			int z = st.query(0, y + 1);
			ckmin(ans[t], x + ind[y] + z);
		}
	}
	st.clear();
	for (auto &[x, t, y] : query) {
		if (t <= 0) {
			st.upd(y, -t - x + ind[y]);
		}else {
			int z = st.query(y, sz(ind));
			ckmin(ans[t], x - ind[y] + z);
		}
	}
	st.clear();
	reverse(all(query));
	for (auto &[x, t, y] : query) {
		if (t <= 0) {
			st.upd(y, -t + x - ind[y]);
		}else {
			int z = st.query(0, y + 1);
			ckmin(ans[t], -x + ind[y] + z);
		}
	}
	st.clear();
	for (auto &[x, t, y] : query) {
		if (t <= 0) {
			st.upd(y, -t + x + ind[y]);
		}else {
			int z = st.query(y, sz(ind));
			ckmin(ans[t], -x - ind[y] + z);
		}
	}
	FOR(i, 1, q + 1) cout << ans[i] << '\n';
}

int32_t main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    setIO("slingshot");
    while (testcase--)
    {
        solve();
    }
}