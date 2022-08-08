// Copyright © 2022 YoungMax Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

#pragma region TEMPLATE

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
constexpr bool ckMax(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
constexpr bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }
ll cdiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // divide a by b rounded down

#ifdef LOCAL
#include "miscellaneous/debug.h"
#else
#define dbg(...) 42
#endif

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

#pragma endregion TEMPLATE

/**
 * Description: Generic segment tree with lazy propagation
 * Source: Inspired by Jiangly - https://codeforces.com//contest/1672/submission/154766851
 * Verification: https://cses.fi/problemset/task/1735
 * Time Complexity: O(n) build, O(log n) per update/query
 */

template<typename T, typename U, typename Merge = plus<T>>
struct SegTreeLazy{
	int sz;
	const Merge merge;
	vector<T> t;
	vector<U> lazy;
	SegTreeLazy(int n) : merge(Merge()) {
		sz = 1;
		while (sz < n) sz *= 2;
		t.resize(sz * 2);
		lazy.resize(sz * 2);
	}
	void build(const vector<T> &vec, int x, int l, int r) {
	    if (r - l == 1) {
	        if (l < (int)vec.size())
	            t[x] = vec[l];
	        return;
	    }
	    int mid = (l + r) / 2;
	    build(vec, 2 * x + 1, l, mid);
	    build(vec, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void build(const vector<T> &vec) {
	    build(vec, 0, 0, sz);
	}
	void upd(int i, const T& v, int x, int l, int r) {
		push(x, l, r);
	    if (r - l == 1) {
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
	void upd(int i, const T& v) {
	    upd(i, v, 0, 0, sz);
	}
	void range_upd(int l, int r, U v, int x, int lx, int rx) {
		push(x, lx, rx);
		if (lx >= r || rx <= l) return;
		if (lx >= l && rx <= r) {
			lazy[x] = lazy_on_lazy(lazy[x], v);
			push(x, lx, rx);
			return;
		}
		int mid = (lx + rx) / 2;
		range_upd(l, r, v, 2 * x + 1, lx, mid);
		range_upd(l, r, v, 2 * x + 2, mid, rx);
		t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void range_upd(int l, int r, U v) {
		range_upd(l, r, v, 0, 0, sz);
	}
	T query(int l, int r, int x, int lx, int rx) {
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
	T query(int l, int r) {
	    return query(l, r, 0, 0, sz);
	}
	void push(int x, int l, int r) {
		if (lazy[x] == U()) return;
		t[x] = lazy_on_val(t[x], lazy[x], l, r);
		if (r - l > 1) {
			lazy[2 * x + 1] = lazy_on_lazy(lazy[2 * x + 1], lazy[x]);
			lazy[2 * x + 2] = lazy_on_lazy(lazy[2 * x + 2], lazy[x]);
		}
		lazy[x] = U();
	}
	U lazy_on_lazy(U oldV, U newV) {
		return oldV + newV;
	}
	T lazy_on_val(T val, U la, int l, int r) {
		return val + la;
	}
};

struct Max {
	ll x;
	int from;
	Max(ll x_ = -LINF, int from_ = -1) : x(x_), from(from_) {}
	Max operator+(const Max& o) const {
		if (x < o.x) return o;
		if (x > o.x) return *this;
		return {x, max(from, o.from)};
	}
	Max operator+(const ll& o) const {
		return {x + o, from};
	}
};

void solve() {
	int n; cin >> n;
	vi ind;
	vi xs(n), ys(n), cs(n), id(n);
	for (int i = 0; i < n; i++) {
		cin >> xs[i] >> ys[i] >> cs[i];
		ind.pb(xs[i]), ind.pb(ys[i]);
	}
	sort(all(ind)), ind.erase(unique(all(ind)), end(ind));
	iota(all(id), 0); sort(all(id), [&](int i, int j) {
		int ii = max(xs[i], ys[i]);
		int jj = max(xs[j], ys[j]);
		return ii != jj ? ii < jj : cs[i] < cs[j];
	});
	auto get_ind = [&](int x) -> int {
		return lb(all(ind), x) - ind.begin();
	};
	vector<Max> a(sz(ind));
	for (int i = 0; i < sz(ind); i++) {
		a[i].x = ind[i];
		a[i].from = i;
	}
	SegTreeLazy<Max, ll> seg(sz(ind));
	seg.build(a);
	ll ans = 0;
	int hi{2*INF}, lo{2*INF};
	for (auto &i : id) {
		int x = xs[i], y = ys[i], c = cs[i];
		x = get_ind(x), y = get_ind(y);
		seg.range_upd(0, min(x, y)+1, c);
		int upper = max(x, y);
		auto [q, from] = seg.query(0, upper+1);
		ll ret = q - ind[upper];
		if (ckmax(ans, ret)) {
			hi = ind[upper], lo = ind[from];
		}
	}
	cout << ans << '\n';
	cout << lo << ' ' << lo << ' ' << hi << ' ' << hi << '\n';
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
