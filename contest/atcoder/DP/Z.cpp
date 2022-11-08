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

struct Line {
	ll m, b;
	ll operator()(ll x) { return m*x + b; }
	friend bool cross(Line l, Line f, Line s) {
		return (__int128_t)(l.b-s.b)*(s.m-f.m) > (__int128_t)(s.m-l.m)*(f.b-s.b);
	}
	friend ostream& operator<<(ostream& os, Line l) {
		os << '(' << l.m << ',' << l.b << ')';
		return os;
	}
};

void solve() {
	int n; ll c;
	cin >> n >> c;
	vl h(n);
	vl dp(n);
	for (auto &e : h) cin >> e;
	
	deque<Line> deq;
	deq.pb({-2*h[0], h[0]*h[0] + dp[0]});
	for (int i = 1; i < n; i++) {
		while (sz(deq) > 1 && deq[0](h[i]) >= deq[1](h[i])) {
			deq.pop_front();
		}
		dbg(deq[0], h[i]);
		dp[i] = deq[0](h[i]) + h[i]*h[i] + c;
		dbg(dp[i], i, deq);
		Line l{-2*h[i], h[i]*h[i] + dp[i]};
		while(sz(deq) > 1 && !cross(l, deq[sz(deq)-1], deq[sz(deq)-2])) { deq.pop_back(); }
		deq.pb(l);
		dbg(deq);
	}
	cout << dp[n - 1] << '\n';
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
