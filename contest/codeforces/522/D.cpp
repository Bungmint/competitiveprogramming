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

constexpr int NAX = 5e5 + 100, SQRT = 750;
int a[NAX], pre[NAX], nxt[NAX], block_id[NAX], n, m;
int b[SQRT][SQRT];
map<int, int> la;

void init() {
	for (int i = 0; i < n; i++) {
		pre[i] = (la.count(a[i]) ? la[a[i]] : -1);
		la[a[i]] = i;
	}
	map<int, int>().swap(la);
	for (int i = n - 1; i >= 0; i--) {
		nxt[i] = (la.count(a[i]) ? la[a[i]] : n);
		la[a[i]] = i;
	}
	map<int, int>().swap(la);
	for (int i = 0; i < n; i++) block_id[i] = i / SQRT;
	memset(b, -1, sizeof(b));
	for (int i = 0; i <= block_id[n - 1]; i++) {
		int L = i*SQRT;
		int cum = -1;
		for (int j = L; j < n; j++) {
			if (pre[j] >= L) {
				if (cum == -1) cum = j - pre[j];
				else cum = min(cum, j - pre[j]);
			}
			if (cum != -1) {
				int& r = b[i][block_id[j]];
				if (r == -1) r = cum;
				else r = min(r, cum);
			}
		}
	}
}

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	init();
	for (int i = 0; i < m; i++) {
		int l, r; cin >> l >> r, l--, r--;
		int ans = -1;
		if (block_id[l] == block_id[r]) {
			for (int j = l; j <= r; j++) {
				if (pre[j] >= l) {
					if (ans == -1) ans = j - pre[j];
					else ans = min(ans, j - pre[j]);
				}
			}
		}else{
			ans = b[block_id[l] + 1][block_id[r] - 1];
			for (int j = (block_id[l] + 1)*SQRT - 1; j >= l; j--) {
				if (nxt[j] <= r) {
					if (ans == -1) ans = nxt[j] - j;
					else ans = min(ans, nxt[j] - j);
				}
			}
			for (int j = (block_id[r])*SQRT; j <= r; j++) {
				if (pre[j] >= l) {
					if (ans == -1) ans = j - pre[j];
					else ans = min(ans, j - pre[j]);
				}
			}
		}
		cout << ans << '\n';
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
