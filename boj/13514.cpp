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
 * Description: Performs range prefix sum queries and point updates. lower_bound returns the first prefix sum >= v
 * Source: Own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=693
 * Time Complexity: O(log n) for query and update
 * 0-indexing
 */

template <typename T>
struct BIT {
	int N; vector<T> bit;
	void init(int n) {
		N = n;
		bit.resize(N + 1);
	}
	void upd(int id, T v) {
		for (id++; id <= N; id += id & -id)
			bit[id] += v;
	}
	T query(int id) {
		T res = 0;
		for (id++; id > 0; id -= id & -id)
			res += bit[id];
		return res;
	}
	T query(int l, int r) {
		return l > r ? 0 : query(r) - query(l - 1);
	}
	T lower_bound(T v) {
		int id = 0;
		T sum = 0;
		int lg = 31 - __builtin_clz(N);
		for (int j = lg; ~j; j--)
		{
			if (id + (1 << j) <= N && sum + bit[id + (1 << j)] < v)
			{
				id += (1 << j);
				sum += bit[id];
			}
		}
		return id;
	}
};


struct Info {
	int root, dist, ind;
};

constexpr int M = 1e5 + 10;
vi g[M];
int s[M], root, dist, ind, max_depth;
vector<Info> infos[M];
vector<BIT<int>> stor[M];
BIT<int> actual[M];
bool vis[M], white[M];

int subtree(int u, int pu = -1) {
	s[u] = 1;
	for (auto &v : g[u]) {
		if (!vis[v] && v != pu) {
			s[u] += subtree(v, u);
		}
	}
	return s[u];
}
int centroid(int u, int tot, int pu = -1) {
	for (auto &v : g[u]) {
		if (!vis[v] && v != pu && 2 * s[u] > tot) 
			return centroid(v, tot, u);
	}
	return u;
}
void dfs(int u, int pu = -1) {
	for (auto &v : g[u]) {
		if (v != pu && !vis[v]) {
			dist++;
			dfs(v, u);
			dist--;
		}
	}
	infos[u].pb({root, dist, ind});
	if (max_depth < dist) max_depth = dist;
}
void cd(int u) {
	int SZ = subtree(u);
	u = centroid(u, SZ);
	stor[u].reserve(sz(g[u]));
	actual[u].init(SZ / 2 + 5);
	root = u;
	for (auto &v : g[u]) {
		if (!vis[v]) {
			dist = max_depth = 1;
			ind = sz(stor[u]);
			dfs(v, u);
			stor[u].pb({});
			stor[u][ind].init(max_depth + 3);
		}
	}
	vis[u] = 1;
	for (auto &v : g[u]) {
		if (!vis[v]) cd(v);
	}
}

void solve() {
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v, u--, v--;
		g[u].pb(v), g[v].pb(u);
	}
	cd(0);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int t, u;
		cin >> t >> u;
		u--;
		if (t == 1) {
			if (white[u]) {
				for (auto &x : infos[u]) {
					BIT<int>& st = stor[x.root][x.ind];
					if (st.lower_bound(1) == x.dist) {
						actual[x.root].upd(x.dist, -1);
						st.upd(x.dist, -1);
						int it = st.lower_bound(1);
						if (it != st.N) actual[x.root].upd(it, 1);
					}else{
						st.upd(x.dist, -1);
					}
				}
				white[u] = 0;
			}else{
				for (auto &x : infos[u]) {
					BIT<int>& st = stor[x.root][x.ind];
					if (int it = st.lower_bound(1); it > x.dist) {
						if (it != st.N) actual[x.root].upd(it, -1);
						st.upd(x.dist, 1);
						actual[x.root].upd(x.dist, 1);
					}else{
						st.upd(x.dist, 1);
					}
				}
				white[u] = 1;
			}
		}else{
			int ans = (white[u] ? 0 : INF);
			if (int it = actual[u].lower_bound(1); it != actual[u].N) {
				ckmin(ans, it);
			}
			for (auto &x : infos[u]) {
				if (white[x.root]) ckmin(ans, x.dist);
				else{
					auto it = actual[x.root].lower_bound(1);
					auto tmp = stor[x.root][x.ind].lower_bound(1);
					if (it != actual[x.root].N) {
						if (it == tmp && tmp != stor[x.root][x.ind].N) {
							auto itit = actual[x.root].lower_bound(2);
							if (itit != actual[x.root].N) {
								ckmin(ans, x.dist + itit);
							}
						}else{
							ckmin(ans, x.dist + it);
						}
					}
				}
			}
			cout << (ans == INF ? -1 : ans) << '\n';
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
