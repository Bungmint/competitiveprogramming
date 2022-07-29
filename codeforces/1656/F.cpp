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

void solve() {
	int n; cin >> n;
	vl a(n + 1), s(n + 1); 
	ll ans = -9*LINF;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(1 + all(a));
	for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
	dbg(s, a);
	// t >= -a_1
	if (s[n] - 2*a[1] + a[1]*n > 0) {
		dbg(s[n], a[1]);
		cout << "INF" << '\n';
		return;
	}else ckmax(ans, a[1]*(s[n] - a[1]) - a[1]*(s[n] - 2*a[1] + a[1]*n));
	// t <= -a_n
	if (s[n] - 2*a[n] + a[n]*n < 0) {
		cout << "INF" << '\n';
		return;
	}else ckmax(ans, a[n]*(s[n] - a[n]) - a[n]*(s[n] - 2*a[n] + a[n]*n));
	for (int i = 1; i < n; i++) {
		if (a[i] == a[i + 1]) continue;
		ll lt = -a[i + 1], rt = -a[i] - 1;
		ll b = -a[1]*a[n] + a[n]*s[i] + a[1]*(s[n] - s[i]);
		ll m = -(a[1] + a[n]) + s[i] + a[n]*i + s[n] - s[i] + (n - i)*a[1];
		ckmax(ans, m*lt + b);
		ckmax(ans, m*rt + b);
	}
	cout << ans << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
