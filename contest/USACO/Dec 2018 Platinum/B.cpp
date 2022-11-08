// Problem: Problem 2. Sort It Out
// Contest: USACO - USACO 2018 December Contest, Platinum
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=865
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
	        return T();
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
};

struct LIS {
	int len;
	ll cnt;
	LIS(int l = 0, ll c = 1) : len(l), cnt(c) {}
	LIS operator+(const LIS& other) const {
		if (len == 0) return other;
		if (other.len == 0) return *this;
		if (len > other.len) return *this;
		if (len < other.len) return other;
		return {len, min(other.cnt + cnt, LINF + 1)};
	}
};

void solve()
{
	int n;
	ll k;
	cin >> n >> k;
	vi a(n);
	for (auto &E : a) cin >> E, E--;
	SegTree<LIS> st(n + 1);
	vector<vi> lis(n + 1);
	vl b(n);
	int mx = 0;
	R0F(i, n) {
		LIS z = st.query(a[i] + 1, n + 1);
		z.len++;
		lis[z.len].pb(i);
		ckmax(mx, z.len);
		b[i] = z.cnt;
		st.upd(a[i], z);
	}
	int last = -1;
	vi vis(n), ans;
	dbg(b);
	ROF(i, 1, mx + 1) {
		sort(all(lis[i]), [&](auto p, auto q) {
			return a[p] > a[q];
		});
		for (auto &e : lis[i]) {
			if (e < last) continue;
			if (b[e] < k) k -= b[e];
			else{
				dbg(e, last);
				vis[e] = 1;
				last = e;
				break;
			}
		}
	}
	F0R(i, n) if (vis[i] == 0) ans.pb(a[i]);
	sort(all(ans));
	cout << sz(ans) << '\n';
	for (auto &e : ans) cout << e + 1 << '\n';
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    setIO("itout");
    while (testcase--)
    {
        solve();
    }
}