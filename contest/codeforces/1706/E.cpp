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


/**
 * Description: Data structure that supports range idempotent queries on a static array
 * Source: Own
 * Verification:
 * Time Complexity: O(nlogn) build, O(1) query
 */

template <typename T>
struct SparseTable{
	vector<vector<T>> spar;
	const T ID = {}; // change this
	inline T merge(const T& a, const T& b) { // change this
		return max(a, b);
	} 
	SparseTable() {}
	SparseTable(const vector<T>& a) {
		int lg = 32 - __builtin_clz(sz(a));
		spar.assign(lg, vector<T>(sz(a), ID));
		for (int i = 0; i < sz(a); ++i) spar[0][i] = a[i];
		for (int j = 1; j < lg; ++j) 
			for (int i = 0; i + (1 << j) <= sz(a); ++i)
				spar[j][i] = merge(spar[j - 1][i], spar[j - 1][i + (1 << (j - 1))]);
	}
	SparseTable(T a[], int n) {
		int lg = 32 - __builtin_clz(n);
		spar.assign(lg, vector<T>(n, ID));
		for (int i = 0; i < n; ++i) spar[0][i] = a[i];
		for (int j = 1; j < lg; ++j) 
			for (int i = 0; i + (1 << j) <= n; ++i)
				spar[j][i] = merge(spar[j - 1][i], spar[j - 1][i + (1 << (j - 1))]);
	}
	T query(int a, int b) {
		assert(a <= b);
		int dif = 31 - __builtin_clz(b - a + 1);
		return merge(spar[dif][a], spar[dif][b - (1 << dif) + 1]);
	}
};

struct MaxLCA {
    vector<vpi> g, up;
    vi depth;
    int LG;
    MaxLCA(int n) : g(n) {
        LG = 32 - __builtin_clz(n);
        up.assign(LG, vpi(n));
        depth.resize(n);
    }
    void add_edge(int u, int v, int w) {
        g[u].pb({v, w});
        g[v].pb({u, w});
    }
    void init(int u = 0, int pu = -1) {
        for (auto &[v, w] : g[u]) {
            if (v == pu) continue;
            depth[v] = depth[u] + 1;
            up[0][v] = {u, w};
            for (int i = 1; i < LG; i++) {
                up[i][v].fi = up[i - 1][up[i - 1][v].fi].fi;
                up[i][v].se = max(up[i - 1][up[i - 1][v].fi].se, up[i - 1][v].se);
            }
            init(v, u);
        }
    }
    int get_max(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int d = depth[u] - depth[v];
        int ans = 0;
        for (int i = LG - 1; i >= 0; i--) {
            if (d >> i & 1) {
                ckmax(ans, up[i][u].se);
                u = up[i][u].fi;
            }
        }
        if (u == v) return ans;
        for (int i = LG - 1; i >= 0; i--) {
            if (up[i][u].fi != up[i][v].fi) {
                ckmax(ans, up[i][u].se);
                ckmax(ans, up[i][v].se);
                u = up[i][u].fi;
                v = up[i][v].fi;
            }
        }
        return max({ans, up[0][u].se, up[0][v].se});
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vpi edges(m);
    vpi query(q);
    vi a(n - 1);
    MaxLCA mst(n);
    DSU dsu(n);
    for (auto &e : edges) cin >> e.fi >> e.se, e.fi--, e.se--;
    for (auto &[l, r] : query) cin >> l >> r, l--, r--;
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        if (dsu.unite(u, v)) {
            mst.add_edge(u, v, i + 1);
        }
    }
    mst.init();
    dbg(mst.up);
    for (int i = 0; i < n - 1; i++) {
        a[i] = mst.get_max(i, i + 1);
    } 
    dbg(a);
    SparseTable spar(a);
    for (int i = 0; i < q; i++) {
        int ans = (query[i].fi == query[i].se ? 0 : spar.query(query[i].fi, query[i].se - 1));
        cout << ans << " \n"[i == q - 1];
    }
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

