// Copyright © 2022 Youngmin Park. All rights reserved.
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
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

#define all(v) (v).begin(), (v).end()
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound

constexpr int INF = 1e9;
constexpr ll LINF = 1e18;
const ld PI = acos((ld)-1.0);
constexpr int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
constexpr bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
constexpr bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

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
template <typename T>
ostream &operator<<(ostream &os, const deque<T> &v) {
	os << vector<T>(all(v));
	return os;
}
template <typename T, typename S, typename C>
ostream &operator<<(ostream &os, priority_queue<T, S, C> pq) {
	vector<T> v;
	while (sz(pq)) {
		v.pb(pq.top());
		pq.pop();
	}
	os << v;
	return os;
}
void dbg_out()
{
	cerr << "\033[0m" << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
	cerr << ' ' << H;
	dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "\033[1;35m" << __func__ << ':' << __LINE__ << " (" << #__VA_ARGS__ << "):\033[33m", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

inline namespace RecursiveLambda
{
	template <typename Fun>
	struct y_combinator_result
	{
		Fun fun_;
		template <typename T>
		explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}
		template <typename... Args>
		decltype(auto) operator()(Args &&...args)
		{
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun)
	{
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

inline namespace Range {
	class ForwardRange {
		int src, dst;

	  public:
	  	explicit constexpr ForwardRange(const int l, const int r) : src(l), dst(r) {}
		explicit constexpr ForwardRange(const int n) : src(0), dst(n) {}
		constexpr ForwardRange begin() const { return *this; }
		constexpr monostate end() const { return {}; }
		constexpr bool operator!=(monostate) const { return src < dst; }
		constexpr void operator++() const {}
		constexpr int operator*() { return src++; }
	};
	class BackwardRange {
		int src, dst;

	  public:
	  	explicit constexpr BackwardRange(const int l, const int r) : src(r), dst(l) {}
		explicit constexpr BackwardRange(const int n) : src(n), dst(0) {}
		constexpr BackwardRange begin() const { return *this; }
		constexpr monostate end() const { return {}; }
		constexpr bool operator!=(monostate) const { return src > dst; }
		constexpr void operator++() const {}
		constexpr int operator*() { return --src; }
	};
	using rep = ForwardRange;
	using per = BackwardRange;
};

/*
 * Description: Generic Iterative Segment Tree 
 * Source: 
        * https://codeforces.com/blog/entry/18051
        * Benq
 * Verification:
 * Time Complexity: O(n) build, O(log n) updates/queries
**/
template <typename T>
struct SegTree{
    const T ID = {-LINF}; 
    T comb(const T& a, const T& b) { return max(a, b); }
    vector<T> seg; int n;
    SegTree(const vector<T>& vec) {
		for (n = 1; n < sz(vec);) n *= 2;
		seg.assign(2 * n, ID);
        for (int i = 0; i < sz(vec); i++) seg[i + n] = vec[i];
        for (int i = n - 1; i; i--) pull(i);
    }
    void pull(int p) { seg[p] = comb(seg[2 * p], seg[2 * p + 1]); }
    void upd(int p, const T& val) {
        seg[p += n] = val;
        for (p /= 2; p; p /= 2) pull(p);
    }
	int first_at_least(ll val, int x, int l, int r) {
		if (seg[x] < val) return -1;
		if (l == r - 1) return l;
		int m = (l + r) / 2;
		int res = first_at_least(val, 2 * x, l, m);
		if (res != -1) return res;
		return first_at_least(val, 2 * x + 1, m, r);
	}
	int first_at_least(ll val) {
		return first_at_least(val, 1, 0, n);
	}
};


void solve()
{
	int n, m;
	cin >> n >> m;
	vl x(n), id(n), t(n), cnt(n), inv(n);
	vl reach(n);
	for (int i : rep(n)) cin >> x[i] >> t[i];
	iota(all(id), 0);
	sort(all(id), [&](int i, int j) {
		return x[i]	< x[j];
	});
	for (int i : rep(n)) {
		reach[i] = x[id[i]] + t[id[i]]; 
	}
	SegTree<long long> seg(reach);
	multiset<pll> st;
	for (int i : rep(m)) {
		int p, b;
		cin >> p >> b;
		st.insert({p, b});
		int r = seg.first_at_least(p);
		if (r == -1) continue;
		int frog = id[r];
		if (x[frog] <= p) {
			auto it = st.lb({x[frog], -LINF});
			while (sz(st) && it != st.end() && it->fi <= x[frog] + t[frog]) {
				t[frog] += it->se;
				cnt[frog]++;
				it = st.erase(it);
			}
			seg.upd(r, t[frog] + x[frog]);
		}
	}
	for (int i : rep(n)) {
		cout << cnt[i] << ' ' << t[i] << '\n';
	}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--)
	{
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
