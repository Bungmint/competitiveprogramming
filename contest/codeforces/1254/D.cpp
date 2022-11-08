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
 * Basic Modular Operations assuming 0 <= a, b < MOD
 * Source: Own
 * Verification:
 * Time complexity: O(log(min(a, b))) for modular inverse and mod_pow, other operations are O(1)
 */

inline namespace ModUtil {
    constexpr int MOD = 998244353;
    int add(int a, const int& b) { 
        a += b;
        if (a >= MOD) a -= MOD;
        return a;
    }
    int mul(const int& a, const int& b) { return 1LL * a * b % MOD; }
    int sub(int a, const int& b) {
        a -= b;
        if (a < 0) a += MOD;
        return a;
    }
    int mod_pow(int a, int b) {
        int r = 1;
        while (b) {
            if (b & 1) r = mul(r, a);
            a = mul(a, a);
            b >>= 1;
        }
        return r;
    }
    template <typename T>
    T inverse(T a, T b) { // Assumes 0 < a < b, could overflow if using 64bit int
        return a > 1 ? b - inverse(b % a, a) * b / a : 1;
    }
}

/**
 * Description: Performs range prefix sum queries and point updates. lower_bound returns the first prefix sum >= v
 * Source: Own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=693
 * Time Complexity: O(log n) for query and update
 * 0-indexing
 */

template <typename T>
struct BIT {
	int N; vector<T> bit;
	BIT(int n) : N(n), bit(n + 1) {}
	void upd(int id, T v) {
		for (id++; id <= N; id += id & -id)
			bit[id] = add(bit[id], v);
	}
	T query(int id) {
		T res = 0;
		for (id++; id > 0; id -= id & -id)
			res = add(res, bit[id]);
		return res;
	}
};

constexpr int M = 2e5;
int subt[M], head[M], depth[M], par[M], pos[M], ti;
int at[M];
BIT<int> bit1(M), bit2(M);
vi adj[M];
int n, q;

namespace RURQ {
	void upd(int l, int r, int v) {
		bit1.upd(l, v); bit1.upd(r + 1, MOD - v);
		bit2.upd(l, mul(l, v)); bit2.upd(r + 1, mul(MOD - v, r + 1));
	}
	int query(int r) {
		return sub(mul(r + 1, bit1.query(r)), bit2.query(r));
	}
	int query(int l, int r) {
		return sub(query(r), query(l - 1));
	}
};


void dfs(int u) {
	subt[u] = 1;
	for (auto &v : adj[u]) {
		adj[v].erase(find(all(adj[v]), u));
		depth[v] = 1 + depth[u];
		par[v] = u;
		dfs(v);
		subt[u] += subt[v];
		if (subt[v] > subt[adj[u][0]]) {
			swap(v, adj[u][0]);
		}
	}
}
void dfs_label(int u) {
	pos[u] = ti++;
	for (auto &v : adj[u]) {
		head[v] = (v == adj[u][0] ? head[u] : v);
		dfs_label(v);
	}
}
void init(int root) {
	head[root] = root;
	par[root] = depth[root] = ti = 0;
	dfs(root);
	dfs_label(root);
}


void solve() {
	cin >> n >> q;
	const int INVN = mod_pow(n, MOD - 2);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v), adj[v].pb(u);
	}
	init(1);
	auto upd = [&](int u, int d) -> void {
		at[u] = add(at[u], d);
		const int outside = mul(d, mul(INVN, subt[u]));
		RURQ::upd(0, pos[u] - 1, outside);
		RURQ::upd(pos[u], pos[u], d);
		RURQ::upd(pos[u] + subt[u], n - 1, outside);
		if (sz(adj[u])) {
			int v = adj[u][0];
			int without = n - subt[v];
			const int z = mul(d, mul(INVN, without));
			RURQ::upd(pos[v], pos[v] + subt[v] - 1, z);
		}
	};
	auto query = [&](int u) -> int {
		int r = RURQ::query(pos[u], pos[u]);
		if (u == 4) dbg(r);
		int pre = u; u = par[u];
		while (u) {
			if (pre == head[pre]) {
				r = add(r, mul(INVN, mul(at[u], sub(n, subt[pre]))));
				pre = u, u = par[u];
			}else{
				pre = head[u];
				u = par[head[u]];
			}
		}
		return r;
	};
	for (int i = 0; i < q; i++) {
		int t; cin >> t;
		if (t == 1) {
			int u, d;
			cin >> u >> d; 
			upd(u, d);
		}else{
			int u;
			cin >> u;
			cout << query(u) << '\n';
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
