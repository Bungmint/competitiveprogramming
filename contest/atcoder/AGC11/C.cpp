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

struct BipartiteDSU {
	vpi e;
	vector<bool> is_bi;
	BipartiteDSU(int N) {
		e = vpi(N, {-1, 0});
		is_bi = vector<bool>(N, 1);
	}
	pii get(int x) {
		if (e[x].fi < 0) return {x, 0};
		pii px = get(e[x].fi);
		e[x].se ^= px.se;
		e[x].fi = px.fi;
		return e[x];
	}
	int size(int x) { return -e[get(x).fi].fi; }
	void unite(int x, int y) {
		pii xx = get(x), yy = get(y);
		if (xx.fi == yy.fi) {
			if (xx.se == yy.se) is_bi[xx.fi] = 0;
			return;
		}
		if (e[xx.fi] > e[yy.fi]) swap(xx, yy);
		e[xx.fi].fi += e[yy.fi].fi, e[yy.fi].fi = xx.fi;
		e[yy.fi].se = xx.se ^ yy.se ^ 1;
		is_bi[xx.fi] = is_bi[yy.fi] && is_bi[xx.fi];
	}
};


void solve() {
	ll n, m;
	cin >> n >> m;
	ll ans{};
	BipartiteDSU dsu(n);
	vector<bool> vis(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v, u--, v--;
		dsu.unite(u, v);
	}
	ll x{}, y{}, z{};
	ll bi_sum{}, nonbi_sum{};
	for (int i = 0; i < n; i++) {
		if (int r = dsu.get(i).fi; !vis[r]) {
			vis[r] = 1;
			int SZ = dsu.size(r); 
			if (SZ == 1) x++;
			else if (dsu.is_bi[r]) y++, bi_sum += SZ;
			else z++, nonbi_sum += SZ;
		}
	}
	ans = n*x + x*bi_sum + 2*y*y + y*z + x*nonbi_sum + y*z + z*z;
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
