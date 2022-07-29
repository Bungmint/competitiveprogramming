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
 * Solution: Digit DP
 */

constexpr int NAX = 2e5 + 10, MOD = 998244353;
int dp[NAX][8][8];
string n;
vi dig;

int add(int a, int b) {
	a += b; if (a >= MOD) a -= MOD;
	return a;
}
int mul(int a, int b) {
	return 1LL * a * b % MOD;
}

int dfs(int pos, int xz, int off) {
	if (pos == sz(dig)) {
		return (xz == 7);
	}
	int& state = dp[pos][xz][off];
	if (state != -1) return state;
	state = 0;
	int cur = dig[pos];
	if (cur) {
		for (int mask = 0; mask < 8; mask++) {
			int x = mask & 1;
			int z = mask>>1 & 1;
			int a = mask>>2 & 1;
			int nxtxz = xz; 
			if (x && z) nxtxz |= 4;
			else if (z) nxtxz |= 2;
			else if (x) nxtxz |= 1;

			int nxtoff = off; 
			if (a == x) nxtoff |= 1;
			if (a == z) nxtoff |= 2;
			if (!a) nxtoff |= 4;

			state = add(state, dfs(pos+1, nxtxz, nxtoff));
		}
	}else{
		for (int mask = 0; mask < 8; mask++) {
			int x = mask & 1;
			int z = mask>>1 & 1;
			int a = mask>>2 & 1;
			int nxtxz = xz; 
			if (x && z) nxtxz |= 4;
			else if (z) nxtxz |= 2;
			else if (x) nxtxz |= 1;

			int nxtoff = off; 
			if ((a ^ x) && !(off & 1)) continue;
			if ((a ^ z) && !(off & 2)) continue;
			if (a && !(off & 4)) continue; 

			state = add(state, dfs(pos+1, nxtxz, nxtoff));
		}
	}
	dbg(pos, xz, off, state);
	return state;
}


void solve() {
	memset(dp, -1, sizeof(dp));
	cin >> n; for (auto &ch : n) dig.pb(ch - '0');
	cout << dfs(0, 0, 0) << '\n';
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
