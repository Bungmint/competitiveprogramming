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

/*
 * Description: Disjoint Set Union with both path compression and size heuristic
 * Source: USACO Guide/Benq
 * Verification:
 * Time complexity: amortized O(\alpha(n)) updates/queries
 */

struct DSU {
	vi e;
	vi queries;
	vi ans;
	DSU(int N, int Q) { 
		e = vi(N, -1); queries = vi(N, -1); 
		ans = vi(Q, -1);
	}
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool same_set(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y, int w) {
		x = get(x), y = get(y);
		if (x == y) return false;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
		if (queries[x] != -1 && queries[y] != -1) {
			if (queries[x] > queries[y]) {
				ans[queries[x]] = w;
			}else{
				ans[queries[y]] = w;
			}
			queries[x] = min(queries[x], queries[y]);
		}else if (queries[y] != -1) queries[x] = queries[y];
		return true;
	}
};

struct Edge {
	int u, v, w;
	bool operator<(const Edge& o) const {
		return w < o.w;
	}
};

void solve() {
	int n, m, q;
	cin >> n >> m >> q;
	vector<Edge> edges(m);
	DSU dsu(n, q);
	for (auto &[u, v, w] : edges) {
		cin >> u >> v >> w;
		u--, v--;
	}
	for (int i = 0; i < q; i++) {
		int x;
		cin >> x, x--;
		dsu.queries[x] = i;
	}
	sort(all(edges));
	for (auto &[u, v, w] : edges) {
		dsu.unite(u, v, w);
	}
	for (int i = 1; i < q; i++) {
		if (dsu.ans[i - 1] == -1) continue;
		if (dsu.ans[i] == -1) dsu.ans[i] = dsu.ans[i - 1];
		else ckmin(dsu.ans[i], dsu.ans[i - 1]);
	}
	for (int i = 0; i < q; i++) {
		cout << dsu.ans[i] << '\n';
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
