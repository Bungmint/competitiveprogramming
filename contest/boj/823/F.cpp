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
	int N, M;
	cin >> N >> M;
	vector<vpi> adj(N);
	vl dist(N, LINF);
	vi last_length(N, -1);
	for (int i = 0; i < M; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		adj[u].eb(w, v);
		adj[v].eb(w, u);
	}
	for (int i = 0; i < N; i++) {
		sort(all(adj[i]), greater<pii>());
	}
	int st, en;
	cin >> st >> en;
	st--, en--;
	dist[st] = 0;
	pqg<tuple<ll, int, int>> pq;
	pq.emplace(0, 0, st);
	while (sz(pq)) {
		auto [d, last, u] = pq.top();
		pq.pop();
		int &len = last_length[u];
		if (len == sz(adj[u]) - 1 || 
			adj[u][len + 1].fi <= last) 
				continue;
		while (len + 1 < sz(adj[u]) &&
				adj[u][len + 1].fi > last) {
					auto [w, v] = adj[u][len + 1];
					ckmin(dist[v], d + w);
					pq.emplace(d + w, w, v);
					len++;
				}
	}
	if (dist[en] == LINF) cout << "DIGESTA\n";
	else cout << dist[en] << '\n';
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
