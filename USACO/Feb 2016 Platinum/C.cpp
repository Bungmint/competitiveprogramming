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

struct Line {
	ll m, b;
	ll operator()(ll x) { return m*x + b; }
	friend bool cross(Line ins, Line x, Line y) {
		return (ins.b-x.b) * (y.m-x.m) < (ins.m-x.m) * (y.b-x.b);
	}
};


void solve() {
	int n, k; cin >> n >> k;
	vi r(n);
	for (auto &e : r) cin >> e;
	if (n <= k) {
		cout << 0 << '\n';
		return;
	}
	reverse(all(r));
	ll ans{LINF};
	for (int iter = 0; iter < n; iter++) {
		vector<deque<Line>> hull(k+1);
		vl s(n), t(n);
		for (int i = 0; i < n; i++) {
			s[i] = r[i];
			t[i] = 1LL*r[i]*i;
			if (i) s[i] += s[i-1], t[i] += t[i-1];
		}
		dbg(s, n);
		hull[1].pb({-s[0], t[0]});
		for (int i = 1; i < n; i++) {
			for (int j = 1; j < k; j++) {
				if (sz(hull[j]) == 0) break;
				while (sz(hull[j]) > 1 && hull[j][0](i) > hull[j][1](i)) {
					hull[j].pop_front();
				}
				ll dp_ik = hull[j][0](i) + 1LL*s[i]*i - t[i];
				Line ins = {-s[i], dp_ik+t[i]};
				while (sz(hull[j+1]) > 1 && !cross(ins, hull[j+1][sz(hull[j+1])-2], hull[j+1][sz(hull[j+1])-1])) {
					hull[j+1].pop_back();
				}
				hull[j+1].pb(ins);
			}
		}
		while (sz(hull[k]) > 1 && hull[k][0](n) > hull[k][1](n)) {
			hull[k].pop_front();
		}
		ckmin(ans, hull[k][0](n) + n*s[n-1] - t[n-1]);
		
		rotate(r.begin(), 1 + all(r));
	}
	cout << ans << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	#ifndef LOCAL
		freopen("cbarn.in", "r", stdin);
		freopen("cbarn.out", "w", stdout);
	#endif
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
