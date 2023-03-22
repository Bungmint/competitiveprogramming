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


/*
 * Description: Disjoint Set Union with both path compression and size heuristic
 * Source: USACO Guide/Benq
 * Verification:
 * Time complexity: amortized O(\alpha(n)) updates/queries
 */

struct DSU {
	vi e;
	DSU(int N) { e = vi(N, -1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool same_set(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) {
		x = get(x), y = get(y);
		if (x == y) return false;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
		return true;
	}
};

void solve() {
    int n, m;
    cin >> n >> m;
    vi ind(m);
    DSU dsu(n);
    vpi es(m);
    vector<vi> tree(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        es[i] = {u, v};
        if (dsu.unite(u, v)) {
            ind[i] = 1;
            tree[u].pb(v), tree[v].pb(u);
        }
    }
    if (m <= n + 1) {
        for (int i = 0; i < m; i++) {
            cout << ind[i];
        }
        cout << "\n";
        return;
    }
    DSU test(n);
    vi oth;
    for (int i = 0; i < m; i++) {
        if (ind[i] == 0) {
            oth.pb(i);
        }
    }
    bool ok = 1;
    set<int> vs;
    for (auto &i : oth) {
        auto [u, v] = es[i];
        vs.insert(u), vs.insert(v);
        if (!test.unite(u, v)) {
            ok = 0;
        }
    }
    dbg(vs, ok);
    if (ok) {
        for (int i = 0; i < m; i++) {
            cout << ind[i];
        }
        cout << "\n"; 
        return;
    }
    vi depth(n), par(n);
    auto dfs = y_combinator([&](auto self, int u, int pu) -> void {
        par[u] = pu;
        for (auto &v : tree[u]) {
            if (v != pu) {
                depth[v] = depth[u] + 1;
                self(v, u);
            }
        }
    });
    dfs(0, -1);
    vi vss(all(vs));
    sort(all(vss), [&](int u, int v) {
             return depth[u] > depth[v];
         });
    dbg(vss);
    int u = vss[0], v = vss[1];
    for (int i = 0; i < m; i++) {
        if (es[i] == make_pair(u, par[u]) || es[i] == make_pair(par[u], u)) {
            dbg(ind[i]);
            dbg(u, par[u]);
            ind[i] = 0;
        }
        if (es[i] == make_pair(u, v) || es[i] == make_pair(v, u)) {
            ind[i] = 1;
        }
    }
    for (int i = 0; i < m; i++) {
        cout << ind[i];
    }
    cout << '\n';
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

