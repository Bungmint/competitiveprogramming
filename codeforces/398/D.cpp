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

struct chash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
    size_t operator()(pair<uint64_t, uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};

const int NAX = 5e4 + 100, LIM = 500;
unordered_set<int> adjH[NAX], adjL[NAX];
vi adj[NAX];
bool on[NAX], big[NAX];
int ans[NAX];

void init(int n) {
	for (int u = 0; u < n; u++) {
		if (sz(adj[u]) >= LIM) big[u] = 1;
	}
	for (int u = 0; u < n; u++) {
		for (auto &v : adj[u]) {
			if (big[v]) adjH[u].insert(v);
			else adjL[u].insert(v), ans[u] += on[v];
		}
	}
}
void to_big(int u) {
	if (big[u] || sz(adjH[u]) + sz(adjL[u]) < LIM) return;
	big[u] = 1;
	for (auto &v : adjH[u]) {ans[v] -= on[u]; adjL[v].erase(u); adjH[v].insert(u);}
	for (auto &v : adjL[u]) {ans[v] -= on[u]; adjL[v].erase(u); adjH[v].insert(u);}
}
void to_small(int u) {
	if (!big[u] || sz(adjH[u]) + sz(adjL[u]) >= LIM) return;
	big[u] = 0;
	for (auto &v : adjH[u]) {ans[v] += on[u]; adjH[v].erase(u); adjL[v].insert(u);}
	for (auto &v : adjL[u]) {ans[v] += on[u]; adjH[v].erase(u); adjL[v].insert(u);}
}
void add_edge(int u, int v) {
	if (big[u]) adjH[v].insert(u);
	else adjL[v].insert(u), ans[v] += on[u];
	if (big[v]) adjH[u].insert(v);
	else adjL[u].insert(v), ans[u] += on[v];
	to_big(u), to_big(v);
}
void remove_edge(int u, int v) {
	if (big[u]) adjH[v].erase(u);
	else adjL[v].erase(u), ans[v] -= on[u];
	if (big[v]) adjH[u].erase(v);
	else adjL[u].erase(v), ans[u] -= on[v];
	to_small(u), to_small(v);
}
void light_on(int u) {
	on[u] = 1;
	if (big[u]) return;
	for (auto &v : adjL[u]) ans[v]++;
	for (auto &v : adjH[u]) ans[v]++;
}
void light_off(int u) {
	on[u] = 0;
	if (big[u]) return;
	for (auto &v : adjL[u]) ans[v]--;
	for (auto &v : adjH[u]) ans[v]--;
} 
int count_on(int u) {
	int cnt{};
	for (auto &v : adjH[u]) cnt += on[v];
	return cnt + ans[u];
}



void solve() {
	int n, m, q;
	cin >> n >> m >> q;
	int o; cin >> o;
	for (int i = 0; i < o; i++) {
		int u; cin >> u; u--; 
		on[u] = 1;
	}
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		u--, v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	init(n);
	for (int i = 0; i < q; i++) {
		char t; cin >> t;
		if (t == 'O') {
			int u; cin >> u; u--;
			light_on(u);
		}else if (t == 'F') {
			int u; cin >> u; u--;
			light_off(u);
		}else if (t == 'C') {
			int u; cin >> u; u--;
			cout << count_on(u) << '\n';
		}else if (t == 'A') {
			int u, v; cin >> u >> v, u--, v--;
			add_edge(u, v);
		}else{
			int u, v; cin >> u >> v, u--, v--;
			remove_edge(u, v);
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
