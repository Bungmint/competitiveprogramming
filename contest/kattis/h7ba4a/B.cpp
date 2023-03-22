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
#define eb emplace_back
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

using ull = unsigned long long;
constexpr int MAXN = 25111;
ull s[MAXN][4];
vector<pair<ull, ull>> g[MAXN];
ull ans = numeric_limits<ull>::max();
int N;

void dfs(int u, int pu) {
    s[u][0] = 1;
    for (auto &[v, w] : g[u]) {
        if (v == pu) continue;
        dfs(v, u);
        s[u][0] += s[v][0];
        s[u][1] += s[v][1] + s[v][0] * w;
        s[u][2] += s[v][2] + 2 * w * s[v][1] + w * w * s[v][0];
        s[u][3] += s[v][3] + 3 * w * s[v][2] + 3 * w * w * s[v][1] + w * w * w * s[v][0];
    }
}
void dfs_calc(int u, int pu) {
    ckmin(ans, s[u][3]);
    for (auto &[v, w] : g[u]) {
        if (v == pu) continue;
        ull tmp[4], t[4]{};
        copy(s[v], s[v] + 3, tmp);
        t[0] = s[u][0] - s[v][0];
        t[1] = s[u][1] - (s[v][1] + w * s[v][0]);
        t[2] = s[u][2] - (s[v][2] + 2 * w * s[v][1] + w * w * s[v][0]); 
        t[3] = s[u][3] - (s[v][3] + 3 * w * s[v][2] + 3 * w * w * s[v][1] + w * w * w * s[v][0]);
        s[v][0] += t[0];
        s[v][1] += t[1] + t[0] * w;
        s[v][2] += t[2] + 2 * w * t[1] + w * w * t[0];
        s[v][3] += t[3] + 3 * w * t[2] + 3 * w * w * t[1] + w * w * w * t[0];
        dfs_calc(v, u);
        copy(tmp, tmp + 3, s[v]);
    } 
}

void solve() {
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w, u--, v--;
        g[u].pb({v, w}), g[v].pb({u, w});
    }
    dfs(0, -1);
    dfs_calc(0, -1);
    cout << ans * 2 << '\n';
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

