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
	int n, xy, yz, zx;
	cin >> n >> xy >> yz >> zx;
	vpi adj;
	if ((xy+yz+zx) & 1) {
		cout << "NO\n";
		return;
	}
	int x = (xy+zx-yz)/2;
	int y = xy - x;
	int z = zx - x;
	if (x < 0 || y < 0 || z < 0 || x + y + z + 1 > n) {
		cout << "NO\n";
		return;
	}  
	vi val = {x, y, z};
	set<int> todo;
	dbg(x, y, z);
	if (x == 0 || y == 0 || z == 0) {
		vi ind(n-3); iota(all(ind), 4);
		todo = set<int>(all(ind));
		int mid = (val[0] ? (val[1] ? 3 : 2) : 1);
		for (int uu = 1; uu <= 3; uu++) {
			if (uu == mid) continue;
			int u = uu;
			for (int i = 1; i < val[uu-1]; i++) {
				
				int nxt = *todo.begin();
				todo.erase(todo.begin());
				adj.pb({u, nxt});
				u = nxt;
			}
			adj.pb({u, mid});
		}
		// dbg();
	}else{
		// dbg();
		vi ind(n-4); iota(all(ind), 5);
		todo = set<int>(all(ind));
		for (int uu = 1; uu <= 3; uu++) {
			int u = uu;
			for (int i = 1; i < val[uu-1]; i++) {
				int nxt = *todo.begin();
				todo.erase(todo.begin());
				adj.pb({u, nxt});
				u = nxt;
			}
			adj.pb({u, 4});
		}
	}
	cout << "YES\n";
	for (auto &xx : todo) adj.pb({xx, 1});
	for (auto &[u, v] : adj) cout << u << ' ' << v << '\n';
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
