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
 * Description: Dynamic Segment Tree with no lazy propagation
    * Half-open intervals are used for ranges 
 * Source: USACO Guide
 * Verification: https://oj.uz/problem/view/IZhO12_apple
 * Time Complexity: O(log SZ)
 * Memory Complexity: O(QlogSZ)
 */

template <typename T>
struct Node {
    T ans;
	bool lazy;
    Node *l, *r;  
    Node() : ans(T()), lazy(0), l(nullptr), r(nullptr) {}
    T merge(const T& a, const T& b) { return a + b; }
	void push(int lx, int rx) {
		if (!lazy) return;
		ans = rx - lx;
		if (rx - lx == 1) return;
		if (!l) l = new Node();
		if (!r) r = new Node();
		l->lazy = r->lazy = 1;
		lazy = 0; 
	}
	void range_upd(int lo, int hi, int lx, int rx) {
		push(lx, rx);
		if (lo >= rx || hi <= lx) return;
		if (lo <= lx && rx <= hi) {
			lazy = 1;
			push(lx, rx);
			return;
		}
		int mx = (lx + rx) / 2;
		if (!l) l = new Node();
		if (!r) r = new Node();
		l->range_upd(lo, hi, lx, mx);
		r->range_upd(lo, hi, mx, rx);
		ans = merge(l->ans, r->ans);
	}
    T query(int lo, int hi, int lx, int rx) {
		push(lx, rx);
        if (lo >= rx || hi <= lx) return T();
        if (lo <= lx && rx <= hi) { dbg(lx, rx, ans); return ans;}
        int mx = (lx + rx) / 2;
		T lef = (l ? l->query(lo, hi, lx, mx) : T());
		T rig = (r ? r->query(lo, hi, mx, rx) : T());
        return merge(lef, rig);
    }
};
Node<int>* root = new Node<int>();



void solve() {
	int Q, C{};
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		dbg();
		int t, x, y;
		cin >> t >> x >> y;
		dbg(x, y);
		if (t == 1) {
			cout << (C = root->query(x + C, y + C + 1, 1, INF + 1)) << '\n';
		}else{
			root->range_upd(x + C, y + C + 1, 1, INF + 1);
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
