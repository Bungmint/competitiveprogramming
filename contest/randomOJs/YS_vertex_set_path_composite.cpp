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

/**
 * Description: Generic segment tree without lazy propagation
 * Source: Inspired by Jiangly - https://codeforces.com//contest/1672/submission/154766851
 * Verification:
 * Time Complexity: O(n) build, O(log n) per update/query
 */

template <typename T, typename Merge = plus<T>>
struct SegTree{
	int sz;
	const Merge merge;
	vector<T> t;
	SegTree(int n) : merge(Merge()) {
		sz = 1;
		while (sz < n) sz *= 2;
		t.resize(sz * 2);
	}
	void build(const vector<T> &vec, int x, int l, int r) {
	    if (r - l == 1) {
	        if (l < (int)vec.size())
	            t[x] = vec[l];
	        return;
	    }
	    int mid = (l + r) / 2;
	    build(vec, 2 * x + 1, l, mid);
	    build(vec, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void build(const vector<T> &vec) {
	    build(vec, 0, 0, sz);
	}
	void upd(int i, const T& v, int x, int l, int r) {
	    if (r - l == 1) {
	        t[x] = v;
	        return;
	    }
	    int mid = (l + r) / 2;
	    if (i < mid)
	        upd(i, v, 2 * x + 1, l, mid);
	    else
	        upd(i, v, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void upd(int i, const T& v) {
	    upd(i, v, 0, 0, sz);
	}
	T query(int l, int r, int x, int lx, int rx) {
	    if (lx >= r || rx <= l)
	        return T();
	    if (lx >= l && rx <= r)
	        return t[x];
	    int mid = (lx + rx) / 2;
	    T a = query(l, r, 2 * x + 1, lx, mid);
	    T b = query(l, r, 2 * x + 2, mid, rx);
	    return merge(a, b);
	}
	T query(int l, int r) {
	    return query(l, r, 0, 0, sz);
	}
};

// TODO: Test implementation
/**
 * Heavy-Light Decomposition to accompany subtree queries/updates
 * Source: Benq ORZORZ How so ORZ
 * Verification:
 * Time complexity: O(log^2(n)) per query, O(logn) per update
 */

template <typename T, int SZ, bool VAL_IN_EDGES>
struct HLD {
    int N; vi adj[SZ];
    int par[SZ], head[SZ], depth[SZ], subt[SZ], ti;
    int pos[SZ]; vi revpos;
	SegTree<T> revseg{SegTree<T>(SZ)};
	SegTree<T, multiplies<T>> seg{SegTree<T, multiplies<T>>(SZ)};
    void add_edge(int u, int v) { adj[u].pb(v), adj[v].pb(u); }
    void dfs_sz(int u) {
        subt[u]++;
        for (auto &v : adj[u]) {
            par[v] = u, depth[v] = depth[u] + 1;
            adj[v].erase(find(all(adj[v]), u));
            dfs_sz(v);
            subt[u] += subt[v];
            if (subt[v] > subt[adj[u][0]]) swap(v, adj[u][0]);
        }
    }
    void dfs_label(int u) {
        pos[u] = ti++; revpos.pb(u);
        for (auto &v : adj[u]) {
            head[v] = (v == adj[u][0] ? head[u] : v);
            dfs_label(v); 
        }
    }
    void init(int _N, int root = 0) {
        N = _N;
        par[root] = depth[root] = ti = 0; dfs_sz(root); 
        head[root] = root; dfs_label(root);
    }
    // int lca(int x, int y) {
    //     for (; head[x] != head[y]; y = par[head[y]]) {
    //         if (depth[head[x]] > depth[head[y]]) swap(x, y);
    //     }
    //     return depth[x] < depth[y] ? x : y;
    // }
    // int dist(int x, int y) {
    //     return depth[x] + depth[y] - 2 * depth[lca(x, y)];
    // }
    void modify_vertex(int x, T v) {
		seg.upd(pos[x], v);
		revseg.upd(pos[x], v);
    }
	T query_path(int x, int y) {
		T rx{}, ry{};
		while (head[x] != head[y]) {
			if (depth[head[x]] > depth[head[y]]) {
				rx = rx + seg.query(pos[head[x]], pos[x] + 1);
				x = par[head[x]];
			}else{
				ry = revseg.query(pos[head[y]], pos[y] + 1) + ry;
				y = par[head[y]];
			}
		}
		if (depth[x] > depth[y]) {
			return (rx + seg.query(pos[y], pos[x] + 1)) + ry;
		}else{
			return (rx + revseg.query(pos[x], pos[y] + 1)) + ry;
		}
	}
};
constexpr int MOD = 998244353;

int mul(int x, int y) { return 1LL * x * y % MOD; }
int add(int x, int y) { x += y; 
	if (x >= MOD) x -= MOD;
	return x; 
}

struct Linear {
	int a, b;
	Linear(int aa = 1, int bb = 0) : a(aa), b(bb) {}
	Linear operator+(const Linear& other) const {
		return {mul(a, other.a), add(mul(b, other.a), other.b)};
	}
	Linear operator*(const Linear& other) const {
		return {mul(a, other.a), add(mul(a, other.b), b)};
	}
};
HLD<Linear, 1 << 18, 0> hld;


void solve() {
	int n, q;
	cin >> n >> q;
	vector<Linear> f(n);
	for (auto &[a, b] : f) cin >> a >> b;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		hld.add_edge(u, v);
	}
	hld.init(n, 0);
	for (int i = 0; i < n; i++) hld.modify_vertex(i, f[i]);
	for (int i = 0; i < q; i++) {
		int t;
		cin >> t;
		if (t) {
			int u, v, x;
			cin >> u >> v >> x;
			auto [a, b] = hld.query_path(u, v);
			dbg(a, b, i);
			cout << add(mul(a, x), b) << '\n';
		}else{
			int u, a, b;
			cin >> u >> a >> b;
			hld.modify_vertex(u, {a, b});
		}
	}
}

signed main() {
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
