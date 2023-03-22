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

/**
 * Description: Fast flow. 
 * Source:
    * ksun: https://codeforces.com/contest/1416/submission/94013395
    * Benq: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Flows%20(12.3)/Dinic.h
 * Verification:
 * Time complexity: O(mn^2) for general graphs, O(m\sqrt{n}) for simple unit capacity networks
 */

template <typename F>
struct Dinic {
    struct Edge {
        int to, rev;
        F cap;
    };
    int N;
    vector<vector<Edge>> adj;
    vi ptr, lvl;
    Dinic(int _N) { N = _N; adj.resize(N); }
    pii add_edge(int a, int b, F cap, F rcap = 0) {
        assert(min(cap, rcap) >= 0);
        adj[a].pb({b, sz(adj[b]), cap});
        adj[b].pb({a, sz(adj[a]) - 1, rcap});
        return {a, sz(adj[a]) - 1};
    }
    F get_edge_flow(pii loc) {
        const Edge& e = adj.at(loc.fi).at(loc.se);
        return adj.at(e.to).at(e.rev).cap;
    }
    // Generate the level graph
    bool bfs(int s, int t) {
        lvl = ptr = vi(N);
        lvl[s] = 1; queue<int> q({s});
        while (sz(q)) {
            int u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (e.cap && !lvl[e.to]) {
                    q.push(e.to);
                    lvl[e.to] = lvl[u] + 1;
                    if (e.to == t) return 1;
                }
            }
        }
        return 0;
    }
    F dfs(int v, int t, F flow) {
        if (v == t) return flow;
        for (int& i = ptr[v]; i < sz(adj[v]); i++) {
            Edge &e = adj[v][i];
            if (lvl[e.to] != lvl[v] + 1 || !e.cap) continue;
            if (F df = dfs(e.to, t, min(flow, e.cap))) {
                e.cap -= df; adj[e.to][e.rev].cap += df;
                return df;
            }
        }
        return 0;
    }
    F get_max_flow(int s, int t) {
        F res{};
        while (bfs(s, t)) {
            while (F df = dfs(s, t, numeric_limits<F>::max())) {
                res += df;
            }
        }
        return res;
    }
};

void solve() {
	int n, m, k;
	cin >> n >> m >> k;
	Dinic<int> dinic(2 + n + m);
	vector<vi> adj(2 + n + m);
	int s = 0, t = 1 + n + m;
	for (int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		b += n;
		pii p = dinic.add_edge(a, b, 1);
		adj[a].pb(p.se);
	}
	for (int i = 1; i <= n; i++) {
		pii p = dinic.add_edge(s, i, 1);
		adj[s].pb(p.se);
	}
	for (int i = n + 1; i <= n + m; i++) {
		pii p = dinic.add_edge(i, t, 1);
		adj[i].pb(p.se);
	}
	cout << dinic.get_max_flow(s, t) << '\n';
	for (int i = 1; i <= n; i++) {
		for (auto &j : adj[i]) {
			if (dinic.get_edge_flow(make_pair(i, j))) {
				cout << i << ' ' << dinic.adj[i][j].to - n << "\n";
				break;
			}
		}
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