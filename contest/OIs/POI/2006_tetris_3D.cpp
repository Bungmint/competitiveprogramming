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

const int MAXN = 1 << 10;

struct Seg1D {
	struct Node {
		int max = 0, lazy = 0;
	}seg[2*MAXN];
	void upd(int l, int r, int v, int x, int lx, int rx) {
		if (l >= rx || r <= lx) return;
		ckmax(seg[x].max, v);
		if (l <= lx && rx <= r) {
			ckmax(seg[x].lazy, v);
			return;
		}
		int mx = (lx + rx) / 2;
		upd(l, r, v, 2*x + 1, lx, mx);
		upd(l, r, v, 2*x + 2, mx, rx);
	}
	void upd(int l, int r, int v) {
		upd(l, r, v, 0, 0, MAXN);
	}
	int query(int l, int r, int x, int lx, int rx) {
		if (l >= rx || r <= lx) return 0;
		if (l <= lx && rx <= r) {
			return seg[x].max;
		}
		int mx = (lx + rx) / 2;
		return max({query(l, r, 2*x + 1, lx, mx),
					query(l, r, 2*x + 2, mx, rx),
					seg[x].lazy});
	}
	int query(int l, int r) {
		return query(l, r, 0, 0, MAXN);
	}
};

struct Seg2D {
	struct Node{
		Seg1D max, lazy;
	}seg[2*MAXN];
	void upd(int x1, int x2, int y1, int y2, int v, int x, int lx, int rx) {
		if (x1 >= rx || x2 <= lx) return;
		seg[x].max.upd(y1, y2, v);
		if (x1 <= lx && rx <= x2) {
			seg[x].lazy.upd(y1, y2, v);
			return;
		}
		int mx = (lx + rx) / 2;
		upd(x1, x2, y1, y2, v, 2*x + 1, lx, mx);
		upd(x1, x2, y1, y2, v, 2*x + 2, mx, rx);
	}
	void upd(int x1, int x2, int y1, int y2, int v) {
		upd(x1, x2, y1, y2, v, 0, 0, MAXN);
	}
	int query(int x1, int x2, int y1, int y2, int x, int lx, int rx) {
		if (x1 >= rx || x2 <= lx) return 0;
		if (x1 <= lx && rx <= x2) {
			return seg[x].max.query(y1, y2);
		}
		int mx = (lx + rx) / 2;
		return max({query(x1, x2, y1, y2, 2*x + 1, lx, mx),
					query(x1, x2, y1, y2, 2*x + 2, mx, rx),
					seg[x].lazy.query(y1, y2)});
	}
	int query(int x1, int x2, int y1, int y2) {
		return query(x1, x2, y1, y2, 0, 0, MAXN);
	}
}seg;



void solve() {
	int D, S, N;
	cin >> D >> S >> N;
	int mx = 0;
	for (int i = 0; i < N; i++) {
		int d, s, w, x, y;
		cin >> d >> s >> w >> x >> y;
		int res = seg.query(x, x + d, y, y + s);
		seg.upd(x, x + d, y, y + s, res + w);
		ckmax(mx, w + res);
	}
	cout << mx << '\n';
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