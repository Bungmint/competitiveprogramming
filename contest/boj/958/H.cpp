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
		if (lazy[x].x == INF) return;
		t[x] = lazy_on_val(t[x], lazy[x], l, r);
		if (r - l > 1) {
			lazy[2 * x + 1] = lazy_on_lazy(lazy[2 * x + 1], lazy[x]);
			lazy[2 * x + 2] = lazy_on_lazy(lazy[2 * x + 2], lazy[x]);
		}
		lazy[x].x = INF;
	}
	U lazy_on_lazy(U oldV, U newV) {
		return newV;
	}
	T lazy_on_val(T val, U la, int l, int r) {
		return la;
	}
};

struct Min {
    int x;
    Min(int _x = INF) : x(_x) {}
    Min operator+(const Min& other) const {
        return {min(x, other.x)};
    }
};

vi ind;
void insert(int x) {
    ind.pb(x);
}
void init() {
    sort(all(ind));
    ind.resize(unique(all(ind)) - ind.begin());
}
int get_ind(int x) {
    return lb(all(ind), x) - ind.begin();
}

void solve() {
    int n, k;	
    cin >> n >> k;
    vector<vpi> lvl(k);
    for (int i = 0; i < n; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        lvl[k - 1].pb({l, r + 1});
        insert(l), insert(r + 1);
    }
    if (k == 1) {
        cout << 0 << '\n';
        return;
    }
    init();
    SegTreeLazy<Min, Min> seg(3 * n + 100);
    for (auto &v : lvl) for (auto &[l, r] : v) {
        l = get_ind(l);
        r = get_ind(r);
    }
    int ans = INF;
    for (auto &[l, r] : lvl[0]) {
        seg.range_upd(l, r, 0);
    }
    for (int L = 1; L < k; L++) {
        vector<pair<pii, int>> todo;
        for (auto &[l, r] : lvl[L]) {
            Min q = seg.query(l, r);
            if (q.x == INF) continue;
            todo.pb({{l, r}, q.x + 1});
            if (L == k - 1) ckmin(ans, q.x + 1);
        }
        for (auto &[p, q] : todo) {
            seg.range_upd(p.fi, p.se, q);
        }
    } 
    cout << (ans == INF ? -1 : ans) << '\n';
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

