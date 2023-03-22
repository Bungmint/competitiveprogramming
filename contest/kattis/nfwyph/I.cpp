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

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vi t(n);
    vector<vi> g(n);
    for (auto &e : t) cin >> e;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].pb(v), g[v].pb(u);
    }
    if (k == 1 && n == 2) {
        cout << "impossible" << '\n';
        return;
    }
    if (find(all(g[0]), n - 1) != g[0].end()) {
        string ans;
        if (k >= 2) {
            for (int i = 0; i < k - 1; i++) ans += 'N'; 
            for (int i = k - 1; i < n - 1; i++) ans += 'S';
            ans += 'N';
        }else{
            for (int i = 0; i < n - k - 1; i++) ans += 'S';
            for (int i = n - k - 1; i < n - 1; i++) ans += 'N';
            ans += 'S';
        }
        cout << ans << '\n';
        return;
    }
    vl dist(n, LINF);
    pqg<pair<ll, int>> pq;
    dist[0] = t[0];
    pq.push({dist[0], 0});
    vector<vi> edges(n);
    while (sz(pq)) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto &v : g[u]) {
            if (ckmin(dist[v], d + t[v])) {
                vi().swap(edges[v]);
                pq.push({dist[v], v});
                edges[v].pb(u);
            }else if (dist[v] == d + t[v]) {
                edges[v].pb(u);
            }
        }
    }
    vector<vi> digraph(n);
    for (int i = 0; i < n; i++) for (auto &u : edges[i]) digraph[u].pb(i);
    vi vis(n);
    vi topsort;
    dbg(digraph);;
    auto dfs = y_combinator([&](auto self, int u) -> void {
                                vis[u] = 1;
                                for (auto &v : digraph[u]) {
                                    if (!vis[v]) self(v);
                                }
                                topsort.pb(u);
                            });
    dfs(0);
    dbg(topsort);
    reverse(all(topsort));
    string ans;
    for (int i = 0; i < n; i++) ans += ' ';
    for (int i = 0; i < k; i++) ans[topsort[i]] = 'N';
    for (int i = k; i < n; i++) ans[topsort[i]] = 'S';
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

