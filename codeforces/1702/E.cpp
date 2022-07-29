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
	vi cnt(n + 1), a(n), b(n);
	vector<vi> ind(n + 1);
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> b[i];
		cnt[a[i]]++, cnt[b[i]]++;
		ind[a[i]].pb(i), ind[b[i]].pb(i);
	}
	for (int i = 0; i < n; i++) {
		if (a[i] == b[i]) {
			cout << "NO\n";
			return;
		}
	}
	if (count(all(cnt), 2) != n) {
		cout << "NO\n";
		return;
	}
	vi vis(n), color(n);
	bool ok = 1;
	auto dfs = y_combinator([&](auto self, int u) -> void {
		vis[u] = 1;
		int nxt = -1;
		for (auto &j : ind[b[u]]) {
			if (j != u) nxt = j;
		}
		if (nxt == -1) {
			ok = 0;
			return;
		}
		if (vis[nxt]) {
			if (color[nxt] == color[u]) {
				ok = 0;
				return;
			}
		}else{
			color[nxt] = color[u] ^ 1;
			self(nxt);
		}
		nxt = -1;
		for (auto &j : ind[a[u]]) {
			if (j != u) nxt = j;
		}
		if (nxt == -1) {
			ok = 0;
			return;
		}
		if (vis[nxt]) {
			if (color[nxt] == color[u]) {
				ok = 0;
				return;
			}
		}else{
			color[nxt] = color[u] ^ 1;
			self(nxt);
		}
	});
	for (int i = 0; i < n; i++) {
		if (!vis[i]) dfs(i);
	}
	cout << (ok ? "YES" : "NO") << '\n';
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
