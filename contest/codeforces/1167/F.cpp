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

constexpr int MOD = 1e9 + 7, M = 5e5 + 100;
int n;
int mul(int a, int b) {
	return 1LL*a*b%MOD;
}
int add(int a, int b) {
	a += b; 
	if (a >= MOD) a -= MOD;
	return a;
}
int sub(int a, int b) {
	a -= b;
	if (a < 0) a += MOD;
	return a;
}

struct RURQ {
	int bit[M], ibit[M];
	
	void _upd(int i, int v, int vv) {
		for (i++; i <= n; i += i & -i) {
			bit[i] = add(bit[i], v);
			ibit[i] = add(ibit[i], vv);
		}
	}
	void upd(int l, int r, int v) {
		_upd(l, v, mul(l, v));
		_upd(r + 1, MOD - v, mul(r + 1, MOD - v));
	}
	pii _q(int i) {
		pii r;
		for (i++; i; i -= i & -i) {
			r.fi = add(r.fi, ibit[i]);
			r.se = add(r.se, bit[i]);
		}
		return r;
	}
	int query(int r) {
		auto [x, y] = _q(r);
		return sub(mul(r + 1, y), x);
	}
	int query(int l, int r) {
		return sub(query(r), query(l - 1));
	}
};
RURQ lef, rig;

void solve() {
	cin >> n;
	vi a(n), ind(n);
	int ans{};
	iota(all(ind), 0);
	for (auto &e : a) cin >> e;
	sort(all(ind), [&](int i, int j) {
		return a[i] < a[j];
	});
	int sum{};
	for (auto &id : ind) {
		sum = add(sum, mul(id + 1, n - id));
		int coef = sub(sum, add(lef.query(id - 1), rig.query(id + 1, n - 1)));
		dbg(coef, id);
		
		ans = add(ans, mul(coef, a[id]));
		lef.upd(id, n - 1, id + 1);
		rig.upd(0, id, n - id);
	}
	cout << ans << '\n';
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
