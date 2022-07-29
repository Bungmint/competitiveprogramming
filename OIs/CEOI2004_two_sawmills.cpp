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

using Line = pll;

void solve() {
	int n; cin >> n;
	vl w(n), d(n);
	ll sum{}, ans{numeric_limits<ll>::max()};
	for (int i = 0; i < n; i++) {
		cin >> w[i] >> d[i];
	}
	for (int i = n - 2; i >= 0; i--) {
		d[i] += d[i + 1];
	}
	for (int i = 0; i < n; i++) {
		sum += w[i]*d[i];
		if (i) w[i] += w[i - 1];
	}
	deque<Line> stck;
	stck.pb({w[0], -w[0]*d[0]});
	for (int i = 1; i < n; i++) {
		dbg(stck);
		ll cur = sum - d[i]*w[i];
		ll x = d[i];
		while (sz(stck) > 1) {
			Line s = stck[sz(stck)-1], t = stck[sz(stck)-2];
			if (t.fi*x+t.se <= s.fi*x+s.se) {
				stck.pop_back();
			}else break;
		}
		cur += x*stck.back().fi+stck.back().se;
		dbg(cur);
		ckmin(ans, cur);
		ll m = w[i], b = -w[i]*d[i];
		while (sz(stck) > 1) {
			Line s = stck[0], t = stck[1];
			if ((b-t.se)*(s.fi-t.fi) <= (m-t.fi)*(s.se-t.se)) {
				stck.pop_front();
			}else break;
		}
		stck.push_front({m, b});
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
