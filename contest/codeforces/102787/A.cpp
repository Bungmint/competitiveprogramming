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
 * Description: Randomized BBST
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/Treap%20(15.3).h
 * Verification:
 * Time complexity: O(log n) per split/merge
 */

using pt = struct Treap*;
struct Treap {
    int pri, val; pt c[2]; // basics
    int sz; 
    Treap(int _val) {
        pri = rng(), val = _val;
        sz = 1;
        c[0] = c[1] = nullptr;
    }
    ~Treap() {
        for (int i = 0; i < 2; i++) delete c[i];
    }
};

// Just for myself: If you are going to change what the pointer is pointing, use pt&

int get_size(pt x) { return x ? x->sz : 0; }
void calc(pt x) {
    pt a = x->c[0], b = x->c[1];
    x->sz = 1 + get_size(a) + get_size(b);
}
pair<pt, pt> split(pt t, int v) { // <= v goes to the left
    if (!t) return {t, t};
    if (t->val > v) {
        auto [l, r] = split(t->c[0], v);
        t->c[0] = r;
        calc(t);
        return {l, t};
    }else{
        auto [l, r] = split(t->c[1], v);
        t->c[1] = l;
        calc(t);
        return {t, r};
    }
}
pair<pt, pt> split_size(pt t, int v) { // size v goes to the left
    if (!t) return {t, t};
    if (get_size(t->c[0]) >= v) {
        auto [l, r] = split_size(t->c[0], v);
        t->c[0] = r;
        calc(t);
        return {l, t};
    }else{
        auto [l, r] = split_size(t->c[1], v - get_size(t->c[0]) - 1);
        t->c[1] = l;
        calc(t);
        return {t, r};
    }
}
pt merge(pt l, pt r) { // all keys in l < all keys in r
    if (!l || !r) return l ? l : r;
    pt t;
    if (l->pri > r->pri) {
        l->c[1] = merge(l->c[1], r);
        t = l;
        calc(t);
        return t;
    }else{
        r->c[0] = merge(l, r->c[0]);
        t = r;
        calc(t);
        return t;
    }
}
void heapify(pt t) {
    if (!t) return;
    pt mx = t;
    for (int i = 0; i < 2; i++) {
        if (t->c[i] && t->c[i]->pri > mx->pri) mx = t->c[i];
    }
    if (mx != t) {
        swap(mx->pri, t->pri);
        heapify(mx);
    }
}
pt build(vi& a, int l, int r) {
    if (r <= l) return nullptr;
    int m = (l + r) / 2;
    pt t = new Treap(a[m]);
    t->c[0] = build(a, l, m);
    t->c[1] = build(a, m + 1, r);
    heapify(t);
    calc(t);
    return t;
}

vi ans;
void dfs(pt t) {
	if (!t) return;
	dfs(t->c[0]);
	ans.pb(t->val);
	dfs(t->c[1]);
}

void solve() {
	int n;
	cin >> n;
	vi tmp(n);
	iota(all(tmp), 1);
	pt root = build(tmp, 0, n);
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		if (a >= b) continue;
		int k = min(b - a, n - b + 1);
		ar<pt, 5> tps;
		pair<pt, pt> p;
		p = split_size(root, a - 1);
		tps[0] = p.fi;
		p = split_size(p.se, k);
		tps[1] = p.fi;
		p = split_size(p.se, b - a - k);
		tps[2] = p.fi;
		p = split_size(p.se, k);
		tps[3] = p.fi;
		tps[4] = p.se;
		root = merge(tps[0], merge(tps[3], merge(tps[2], merge(tps[1], tps[4]))));
	}
	dfs(root);
	for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i == n - 1];
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
