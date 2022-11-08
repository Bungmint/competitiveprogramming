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
constexpr ll LINF = numeric_limits<ll>::max();
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
 * Chinese Remainder Theorem Solver
 * Source: rkm0959's github
 * Verification:
 * Time complexity: O(log(A.se, B.se))
 */

// TODO: Test Imp
/*
 * Basic Modular Operations assuming 0 <= a, b < MOD
 * Source: Own
 * Verification:
 * Time complexity: O(log(min(a, b))) for modular inverse
**/
inline namespace ModUtil {
    int MOD = 1e9 + 7; // 998244353
    int add(int a, const int& b) { 
        a += b;
        if (a >= MOD) a -= MOD;
        return a;
    }
    int mul(const int& a, const int& b) { return 1LL * a * b % MOD; }
    int sub(int a, const int& b) {
        a -= b;
        if (a < 0) a += MOD;
        return a;
    }
    template <typename T>
    T inverse(T a, T b) { // Assumes 0 < a < b, could overflow if using 64bit int
        return a > 1 ? b - inverse(b % a, a) * b / a : 1;
    }
}

pll crt(pll A, pll B) {
	if (A.se == -1 || B.se == -1) return {-1, -1};
	if (A.se == 1 || B.se == 1) return A.se == 1 ? B : A;
	ll g = gcd(A.se, B.se), l = (A.se / g) * B.se;
	if ((B.fi - A.fi) % g) return {-1, -1};
	ll a = A.se / g, b = B.se / g;
	ll mul = (B.fi - A.fi) / g;
	mul = (mul * inverse(a, b)) % b;
	ll ret = mul * A.se + A.fi;
	ret %= l, ret = (ret + l) % l;
	return {ret, l};
}

void solve() {
	int n, en;
	cin >> n >> en;
	vl period(n);
	vector<vl> x(n);
	vector<vl> dist(n);
	const pair<ll, pll> ID = {-1, {-1, -1}};
	vector<vector<pair<ll, pll>>> g(n, vector<pair<ll, pll>>(n, ID));
	map<ll, vpl> mp;
	pll la{-1, -1};
	for (int i = 0; i < n; i++) {
		cin >> period[i];
		x[i].resize(period[i]);
		dist[i].assign(period[i], LINF);
		for (int j = 0; j < period[i]; j++) {
			cin >> x[i][j];
			mp[x[i][j]].pb({i, j});
			if (x[i][j] == en) la = {i, j};
		}
	}
	if (la.fi == -1) {
		cout << -1 << '\n';
		return;
	}
	for (int i = 0; i < n; i++) {
		ll K = period[i];
		for (int j = 0; j < K; j++) {
			if (sz(mp[x[i][j]]) > 1) {
				auto [a, b] = mp[x[i][j]][0];
				auto [c, d] = mp[x[i][j]][1];
				pll ret = crt({b, period[a]}, {d, period[c]});
				if (ret.fi == -1) continue;
				g[a][c] = {d, ret};
				g[c][a] = {b, ret};
			}
		}
	}
	dbg(g);
	pqg<pair<ll, pll>> pq;
	dist[0][0] = 0;
	pq.push({0, {0, 0}});
	while (sz(pq)) {
		auto [i, j] = pq.top().se;
		auto d = pq.top().fi;
		dbg(d, i, j);
		pq.pop();
		if (d > dist[i][j]) continue;
		for (int k = 0; k < n; k++) {
			if (k == i || g[i][k].fi == -1) continue;
			int id = g[i][k].fi;
			auto [a, nn] = g[i][k].se;
			ll nxt = (a >= d ? a : (1LL * (d - a + nn - 1) / nn) * nn + a);
			if (ckmin(dist[k][id], nxt)) {
				pq.push({dist[k][id], {k, id}});
			}
		}
	}
	ll ans{LINF};
	auto [xx, yy] = la;
	for (int i = 0; i < period[xx]; i++) {
		if (dist[xx][i] == LINF) continue;
		dbg(dist[xx][i]);
		if (i <= yy) {
			ckmin(ans, dist[xx][i] + yy - i);
		}else{
			ckmin(ans, dist[xx][i] + period[xx] + yy - i);
		}
	}
	cout << (ans == LINF ? -1 : ans) << '\n';
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
