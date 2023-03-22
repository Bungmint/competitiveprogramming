// Copyright © 2022 Youngmin Park. All rights reserved.
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
#define eb emplace_back
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
        push(2 * x + 1, l, mid);
        push(2 * x + 2, mid, r);
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

struct Min {
    ll x;
    Min(ll _x = LINF) : x(_x) {}
    Min operator+(const Min& other) const {
        return {min(x, other.x)};
    }
    Min operator+(const ll& lazy) const {
        if (x == LINF) return *this;
        return {x + lazy};
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vi a(n), cold(k), hot(k);
    for (auto &e : a) cin >> e, e--;
    for (auto &e : cold) cin >> e;
    for (auto &e : hot) cin >> e;
    SegTreeLazy<Min, ll> seg(k + 2);
    seg.upd(k, cold[a[0]]);
    // dbg(seg.query(a[1] + 1, k + 1).x);
    // dbg(a[1] + 1);
    for (int i = 1; i < n; i++) {
        // dbg(i);
        ll t = (a[i - 1] == a[i] ? hot[a[i]] : cold[a[i]]);
        ll lef = seg.query(0, a[i]).x, rig = seg.query(a[i] + 1, k + 1).x;
        ll mid = seg.query(a[i], a[i] + 1).x;
        // dbg(lef, rig, mid);
        seg.range_upd(0, k + 1, t);
        // dbg(seg.query(0, k + 1).x);
        seg.upd(a[i - 1], min(min(lef, rig) + cold[a[i]], mid + hot[a[i]]));
        // for (int i = 0; i <= k; i++) {
        //     dbg(seg.query(i, i + 1).x);
        // }
        // dbg(seg.query(a[i - 1], a[i - 1] + 1).x);
        // dbg(mid + hot[a[i]]);
        // dbg(seg.query(0, k + 1).x);
        // for (int i = 0; i <= k; i++) {
        //     dbg(seg.query(i, i + 1).x);
        // }
        // dbg(seg.query(0, k + 1).x);
        // dbg(i);
    }
    cout << seg.query(0, k + 1).x << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

