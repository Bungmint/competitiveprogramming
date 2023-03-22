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

void dijkstra(int s, vector<vi>& g, vi& dist) {
    fill(all(dist), INF);
    pqg<pii> pq;
    dist[s] = 0;
    pq.push({dist[s], s});
    while (sz(pq)) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto &v : g[u]) {
            if (ckmin(dist[v], dist[u] + 1)) {
                pq.push({dist[v], v});
            }
        }
    }
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vi a(k);
    vector<vi> g(n);
    vi x(n), y(n);
    for (auto &e : a) cin >> e, e--;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v, u--, v--;
        g[u].pb(v), g[v].pb(u);
    }
    dijkstra(0, g, x);
    dijkstra(n - 1, g, y);
    sort(all(a), [&](int i, int j) { return x[i] - y[i] < x[j] - y[j]; });
    vi sufmax(k);
    for (int i = k - 1; i >= 0; i--) {
        sufmax[i] = y[a[i]];
        if (i + 1 < k) ckmax(sufmax[i], sufmax[i + 1]);
    }
    int res = 0;
    for (int i = 0; i < k - 1; i++) {
        ckmax(res, x[a[i]] + sufmax[i + 1]);
    }
    dbg(x, y);
    dbg(sufmax);
    dbg(res);
    res++, ckmin(res, x[n - 1]);
    cout << res << '\n';
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

