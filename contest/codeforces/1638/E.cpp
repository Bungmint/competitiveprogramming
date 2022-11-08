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

/**
 * Description: Performs range prefix sum queries and point updates. lower_bound returns the first prefix sum >= v
 * Source: Own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=693
 * Time Complexity: O(log n) for query and update
 * 0-indexing
 */

template <typename T>
struct BIT {
	int N; vector<T> bit;
	BIT(int n) : N(n), bit(n + 1) {}
	void upd(int id, T v) {
		for (id++; id <= N; id += id & -id)
			bit[id] += v;
	}
	T query(int id) {
		T res = 0;
		for (id++; id > 0; id -= id & -id)
			res += bit[id];
		return res;
	}
	T query(int l, int r) {
		return l > r ? 0 : query(r) - query(l - 1);
	}
	T lower_bound(T v) {
		int id = 0;
		T sum = 0;
		int lg = 31 - __builtin_clz(N);
		for (int j = lg; ~j; j--) {
			if (id + (1 << j) <= N && sum + bit[id + (1 << j)] < v) {
				id += (1 << j);
				sum += bit[id];
			}
		}
		return id;
	}
};

constexpr int NAX = 1e6 + 100;
BIT<ll> bit(NAX);
set<pair<pii, int>> color_range;
ll lazy[NAX];

int get_color(int id) {
	auto it = prev(color_range.lb({{id+1, -INF}, -INF}));
	return it->se;
}
ll get_val(int id) {
	return bit.query(id);
}
void color() {
	int l, r, c;
	cin >> l >> r >> c;
	l--, r--;
	auto lt = prev(color_range.lb({{l+1, -INF}, -INF}));
	auto rt = prev(color_range.lb({{r+1, -INF}, -INF}));
	if (lt == rt) {
		auto [L, R] = lt->fi;
		auto col = lt->se;
		bit.upd(l, lazy[col]);
		bit.upd(r+1, -lazy[col]);
		color_range.erase(lt);
		if (L == l && R == r) {
			// nothing
		}else if (L == l) {
			color_range.insert({{r+1, R}, col});
		}else if (R == r) {
			color_range.insert({{L, l-1}, col});
		}else{
			color_range.insert({{r+1, R}, col});
			color_range.insert({{L, l-1}, col});
		}
	}else{
		auto lo = *lt, hi = *rt;
		for (auto it = next(lt); it != rt; it++) {
			auto [L, R] = it->fi; auto col = it->se;
			bit.upd(L, lazy[col]);
			bit.upd(R+1, -lazy[col]);
		}
		color_range.erase(lt, next(rt));
		{
			auto R = lo.fi.se; auto col = lo.se;
			bit.upd(l, lazy[col]);
			bit.upd(R+1, -lazy[col]);
			auto L = hi.fi.fi; col = hi.se;
			bit.upd(L, lazy[col]);
			bit.upd(r+1, -lazy[col]);
		}
		if (lo.fi.fi != l) {
			color_range.insert({{lo.fi.fi, l-1}, lo.se});
		}
		if (hi.fi.se != r) {
			color_range.insert({{r+1, hi.fi.se}, hi.se});
		}
	}
	color_range.insert({{l, r}, c});
	bit.upd(l, -lazy[c]);
	bit.upd(r+1, lazy[c]);
}

void solve() {
	int n, q;
	cin >> n >> q;
	color_range.insert({{0, n - 1}, 1});
	for (int i = 0; i < q; i++) {
		string s; cin >> s;
		if (s[0] == 'C') {
			color();
		}else if (s[0] == 'A') {
			int c, x; cin >> c >> x;
			lazy[c] += x;
		}else{
			int id; cin >> id, id--;
			cout << get_val(id) + lazy[get_color(id)] << '\n';
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
