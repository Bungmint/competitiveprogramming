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

struct DSU {
    vi e;
    DSU(int N) : e(N, -1) {}
    int get(int u) { return e[u] < 0 ? u : e[u] = get(e[u]); }
    bool unite(int u, int v) {
        u = get(u), v = get(v);
        if (u == v) return false;
        if (e[u] > e[v]) swap(u, v);
        e[u] += e[v], e[v] = u;
        return true;
    }
};

void solve() {
    int N, M, alpha;
    cin >> N >> M >> alpha;
    vector<vi> g(N);
    vector<ar<int, 3>> edges(M);
    DSU dsu(N);
    for (auto &[w, u, v] : edges) {
        cin >> u >> v >> w, u--, v--;
    }
    sort(all(edges));
    ll L = 0, k = 0;
    int uu, vv;
    for (auto &[w, u, v] : edges) {
        if (!dsu.unite(u, v)) {
            uu = u, vv = v;
            L = w;
            break;
        }
        g[u].pb(v), g[v].pb(u);
    }
    if (L == 0) {
        cout << "Poor girl" << '\n';
        return;
    }
    vi dist(N, INF);
    dist[uu] = 0;
    queue<int> q;
    q.push({uu});
    while (sz(q)) {
        int u = q.front();
        q.pop();
        for (auto &v : g[u]) {
            if (ckmin(dist[v], dist[u] + 1)) q.push(v);
        }
    }
    k = dist[vv] + 1;
    cout << L * L + alpha * k << '\n';

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

