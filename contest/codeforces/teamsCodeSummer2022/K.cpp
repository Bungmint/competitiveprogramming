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

#define div _div

const int MAXN = 1e4 + 100;
int N, P;
int dp[MAXN], fact[MAXN], inv_fact[MAXN];

int add(int a, int b) {
	a += b;
	if (a >= P) a -= P;
	return a;
}
int sub(int a, int b) {
	a -= b;
	if (a < 0) a += P;
	return a;
}
inline int mul(int a, int b) { return 1LL*a*b % P; }
int bin_pow(int a, int b) {
	int r = 1;
	while (b) {
		if (b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}
int inv(int a) { return bin_pow(a, P - 2); }
int div(int a, int b) { return mul(a, inv(b)); }
int binom(int n, int k) {
	if (n < k || n < 0) return 0;
	return mul(fact[n], mul(inv_fact[k], inv_fact[n - k]));
}

void solve() {
	cin >> N >> P;
	fact[0] = 1;
	for (int i = 1; i <= N; i++) fact[i] = mul(fact[i - 1], i);
	inv_fact[N] = inv(fact[N]);
	for (int i = N - 1; i >= 0; i--) {
		inv_fact[i] = mul(inv_fact[i + 1], i + 1);
	}
	const int INV3 = inv(3);
	dp[1] = 0;
	cout << 0 << ' ';
	int invp = INV3;
	for (int i = 2; i <= N; i++) {
		int sum{1}, C{};
		invp = mul(invp, INV3);
		for (int j = 1; j < i; j++) {
			int pij = mul(invp, mul(binom(i, j), 3));
			C = add(C, mul(add(dp[j], 1), pij));
			sum = sub(sum, pij);
		}
		dp[i] = div(add(sum, C), sub(1, sum));
		cout << dp[i] << " \n"[i == N];
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
