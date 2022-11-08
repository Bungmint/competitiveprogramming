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
ll cdiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // divide a by b rounded down

// #ifdef LOCAL
// #include "miscellaneous/debug.h"
// #else
// #define dbg(...) 42
// #endif

inline namespace RecursiveLambda {
	template <typename Fun>
	struct y_combinator_result {
		Fun fun_;
		template <typename T>
		explicit constexpr y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}
		template <typename... Args>
		constexpr decltype(auto) operator()(Args &&...args) const {
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun) {
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};
/**
 * Description: Basic I/O for the builtin 128bit integer
 * Source: https://codeforces.com/blog/entry/75044
 * Verification: https://atcoder.jp/contests/abc129/tasks/abc129_f
 */
using i128 = __int128_t;
istream& operator>>(istream& in, i128& num) { 
    i128 x = 0, f = 1;
    char ch = in.peek();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        in.get();
        ch = in.peek();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        in.get();
        ch = in.peek();
    }
    num = x * f;
    return in;
}
ostream& operator<<(ostream& out, i128 num) {
    string res;
    bool neg = num < 0;
    if (neg) num = -num;
    do {
        res += '0' + (num % 10);
        num /= 10;
    }while (num > 0);
    if (num < 0) {
        res += '-';
    }
    reverse(all(res));
    out << res;
    return out;
}
#define ll i128
/**
 * Description: Generic segment tree with lazy propagation
 * Source: Inspired by Jiangly - https://codeforces.com//contest/1672/submission/154766851
 * Verification: https://cses.fi/problemset/task/1735
 * Time Complexity: O(n) build, O(log n) per update/query
 */
template<typename T, typename U, typename Merge = plus<T>>
struct LazySegTree{
	int sz;
	const Merge merge;
	vector<T> t;
	vector<U> lazy;
	LazySegTree(int n) : merge(Merge()) {
		sz = 1;
		while (sz < n) sz *= 2;
		t.resize(sz * 2);
		lazy.resize(sz * 2);
	}
	void build(const vector<T> &vec, int x, int l, int r)
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
	void build(const vector<T> &vec)
	{
	    build(vec, 0, 0, sz);
	}
	void range_upd(int l, int r, U v, ll lll, int x, int lx, int rx) {
		push(x, lx, rx);
		if (lx >= r || rx <= l) return;
		if (lx >= l && rx <= r) {
			lazy[x] = lazy_on_lazy(lazy[x], v, t[x].l - lll);
			push(x, lx, rx);
			return;
		}
		int mid = (lx + rx) / 2;
		range_upd(l, r, v, lll, 2 * x + 1, lx, mid);
		range_upd(l, r, v, lll, 2 * x + 2, mid, rx);
		t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void range_upd(int l, int r, U v, ll lll) {
		range_upd(l, r, v, lll, 0, 0, sz);
	}
	T query(int l, int r, int x, int lx, int rx)
	{
		push(x, lx, rx);
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
	void push(int x, int l, int r) {
		if (lazy[x] == U()) return;
		t[x] = lazy_on_val(t[x], lazy[x], l, r);
		if (r - l > 1) {
			lazy[2 * x + 1] = lazy_on_lazy(lazy[2 * x + 1], lazy[x], 0);
			lazy[2 * x + 2] = lazy_on_lazy(lazy[2 * x + 2], lazy[x], 
				t[2 * x + 1].len);
		}
		lazy[x] = U();
	}
	U lazy_on_lazy(U oldV, U newV, ll x) {
		auto [st, b, d] = newV;
		return {st + d * x, b, d};
	}
	T lazy_on_val(T val, U la, int l, int r) {
		return val + la;
	}
};

ll floor_sum(ll a, ll b, ll c, ll n) {
	if (!a) return (b / c) * (n + 1);
	if (a >= c || b >= c) {
		return ((a / c) * n + 2 * (b / c)) * (n + 1) / 2 + floor_sum(a % c, b % c, c, n);
	}
	ll m = (a * n + b) / c;
	return m * n - floor_sum(c, c - b - 1, a, m - 1);
}
struct Node {
	ll l, r, len;
	ll sum;
	Node(ll _l = -1, ll _r = -1, ll _len = 0, ll s = 0) : 
		l(_l), r(_r), len(_len), sum(s) {}
	Node operator+(const Node& other) const {
		if (other.l == -1) return *this;
		if (l == -1) return other;
		return {l, other.r, len + other.len, sum + other.sum};
	}
};
struct Lazy {
	ll st, b, d;
	Lazy(ll _s = 0, ll _b = 0, ll _d = 0) : 
		st(_s), b(_b), d(_d) {}
	bool operator==(const Lazy& other) {
		return make_tuple(st, b, d) == make_tuple(other.st, other.b, other.d);
	}
};
Node operator+(const Node& node, const Lazy& lazy) {
	auto [l, r, len, _] = node;
	auto [x, b, d] = lazy;
	ll z = len * x + d * (len - 1) * len / 2LL - b * floor_sum(d, x, b, len - 1);
	return {l, r, len, z};
}



void solve() {
	int n, q;
	cin >> n >> q;
	vi ind;
	vector<ar<int, 4>> query(q);
	for (int i = 0; i < q; i++) {
		int t, l, r;
		cin >> t >> l >> r;
		ind.pb(l), ind.pb(r);
		if (t == 1) {
			int a, b;
			cin >> a >> b;
			query[i] = {l, r, a, b};
		}else query[i] = {l, r, 0, 0};
	}
	sort(all(ind)), ind.erase(unique(all(ind)), end(ind));
	vector<Node> a;
	vi pos(sz(ind));
	for (int i = 0; i < sz(ind); i++) {
		pos[i] = sz(a);
		a.pb({ind[i], ind[i], 1, 0});
		if (i + 1 < sz(ind) && ind[i + 1] > ind[i] + 1) {
			a.pb({ind[i] + 1, ind[i + 1] - 1, ind[i + 1] - ind[i] - 1, 0});
		}
	}
	LazySegTree<Node, Lazy> seg(sz(a));
	seg.build(a);
	auto getIndex = [&](int x) -> int {
		int it = lb(all(ind), x) - ind.begin();
		return pos[it];
	};
	for (auto &[l, r, a, b] : query) {
		ll lll = l;
		l = getIndex(l), r = getIndex(r);
		if (a) {
			seg.range_upd(l, r + 1, {a, b, a}, lll);
		}else{
			cout << seg.query(l, r + 1).sum << '\n';
		}
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
