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

void solve() {
	int n; cin >> n;
	vi a(n); 
	vector<bool> vis(10);
	for (auto &e : a) cin >> e, vis[e%10] = 1;
	bool five = vis[5] || vis[0];
	bool others = 0;
	for (int i = 0; i < 9; i++) {
		if (i % 5 == 0) continue;
		others |= vis[i];
	}
	if (others && five) {
		cout << "NO\n";
		return;
	}
	if (five) {
		if (vis[5] && vis[0]) {
			int la = -1;
			for (auto &e : a) {
				if (e % 10 == 5) {
					e += 5;
					if (la == -1) la = e;
					else if (la != e) {
						cout << "NO\n";
						return;
					}
				}else{
					if (la == -1) la = e;
					else if (la != e) {
						cout << "NO\n";
						return;
					}
				}
			}
			cout << "YES\n";
		}else{
			int la = -1;
			for (auto &e : a) {
				if (la == -1) la = e;
				else if (la != e) {
					cout << "NO\n";
					return;
				}
			}
			cout << "YES\n";
		}
		return;
	}
	int la = -1;
	for (int i = 0; i < n; i++) {
		while (a[i] % 10 != 2) {
			a[i] += a[i] % 10;
		}
		a[i] %= 20;
		if (la == -1) {
			la = a[i];
		}else if (la != a[i]) {
			cout << "NO\n";
			return;
		}
	}
	cout << "YES\n";
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
