#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <list>
#include <chrono>
#include <random>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <utility>
#include <bitset>
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
mt19937_64 rng();
template <typename T>
constexpr bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
constexpr bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

#ifdef LOCAL
#include "miscellaneous/debug.h"
#else
#define dbg(...) 42
#endif

#pragma endregion TEMPLATE

const int MAXN = 1e5 + 100;
int N, M, K;
vector<pair<int, char>> adj[MAXN], rev_adj[MAXN], condensation[MAXN];
vi adj_ABC_rev[MAXN*3], adj_ABC[MAXN*3];
int outdeg_ABC[MAXN*3];
int dp[3][MAXN*3];
int stor[3][MAXN];
int nxt_val[] = {0, 1, 2, 2, 0, 1, 0};
bool vis1[MAXN], vis2[MAXN], vis3[MAXN];
int head[MAXN];
char on_ABC[MAXN];
vi topsort;


/**
 * Find the SCC using Kosaraju, find the edges within the SCC, Do a DP, profit
 * AB, BC, CA, A, B, C
 * bitmasks to represent states
 */
void dfs1(int u) {
	vis1[u] = 1;
	for (auto &[v, ch] : adj[u]) if (!vis1[v]) dfs1(v);
	topsort.pb(u);
}
void dfs2(int u, int r) {
	vis2[u] = 1;
	head[u] = r;
	for (auto &[v, ch] : rev_adj[u]) if (!vis2[v]) dfs2(v, r);
}
void dfs3(int u) {
	vis3[u] = 1;
	for (auto &[v, ch] : condensation[u]) {
		if (!vis3[v]) dfs3(v);
	}
	int mask = on_ABC[u];
	int nxt_ch = nxt_val[mask];
	int z = 0, w = 0;
	for (auto &[v, ch] : condensation[u]) {
		if (mask == 0) {
			for (int i = 0; i < 3; i++) {
				if ((ch-'A') == (i+1)%3) ckmax(stor[i][u], 1 + stor[(i+1)%3][v]);
				else ckmax(stor[i][u], stor[i][v]);
			}
		}else{
			if ((ch-'A')==nxt_ch) ckmax(z, 1 + stor[nxt_ch][v]);
			else ckmax(z, stor[(nxt_ch+2)%3][v]);
			if ((ch-'A')==(nxt_ch+1)%3) ckmax(w, 1 + stor[(nxt_ch+1)%3][v]);
			else ckmax(w, stor[nxt_ch][v]);
		}
	}
	if (mask == 0) return;
	int cnt = __builtin_popcount(mask);
	for (int i = 0; i < 3; i++) {
		stor[i][u] = z;
		if (cnt == 2) {
			if ((1 << i) & mask) {
				if ((1 << ((i+1)%3)) & mask) stor[i][u]++;
			}else{
				stor[i][u] += 2;
			}
		}else{
			if (nxt_ch == i) stor[i][u] = w;
			else if ((1 << i) & mask) stor[i][u] = z;
			else stor[i][u]++;
		}
	}
}
int calc_K_INF() {
	memset(vis1, 0, sizeof(bool)*(N + 5));
	memset(vis2, 0, sizeof(bool)*(N + 5));
	memset(vis3, 0, sizeof(bool)*(N + 5));
	memset(on_ABC, 0, sizeof(char)*(N + 5));
	memset(head, 0, sizeof(int)*(N + 5));
	for (int i = 0; i < 3; i++) memset(stor[i], 0, sizeof(int)*(N + 5));
	topsort.clear();
	for (int i = 0; i < N; i++) {
		vector<pair<int, char>>().swap(condensation[i]);
	}
	for (int i = 0; i < N; i++) {
		if (!vis1[i]) dfs1(i);
	}
	reverse(all(topsort));
	for (auto &u : topsort) {
		if (!vis2[u]) {
			dfs2(u, u);
		}
	}
	for (int u = 0; u < N; u++) {
		for (auto &[v, ch] : adj[u]) {
			if (head[u] == head[v]) {
				on_ABC[head[u]] |= 1 << (ch - 'A');
			}else{
				condensation[head[u]].pb({head[v], ch});
			}
		}
	}
	for (int u = 0; u < N; u++) {
		if (on_ABC[head[u]] == 7) {
			return -1;
		}
	}
	for (int u = 0; u < N; u++) {
		if (!vis3[head[u]]) {
			dfs3(u);
		}
	}
	int res{};
	for (int i = 0; i < 3; i++) {
		ckmax(res, *max_element(stor[i], stor[i] + N));
	}
	return res;
}
void construct_ABC_graph() {
	memset(outdeg_ABC, 0, sizeof(int)*(3*N + 5));
	for (int u = 0; u < N; u++) {
		for (auto [v, ch] : adj[u]) {
			int c = ch - 'A';
			int bef = c - 1; if (bef < 0) bef += 3;
			adj_ABC_rev[3*v + c].pb(3*u + bef); 
			adj_ABC[3*u + bef].pb(3*v + c);
			outdeg_ABC[3*u + bef]++;
		}
	}
}
int check_ABC_cycle() {
	queue<int> q;
	for (int i = 0; i < 3; i++) memset(dp[i], 0, sizeof(int)*(3*N + 5));
	topsort.clear();
	for (int u = 0; u < 3*N; u++) {
		if (outdeg_ABC[u] == 0) q.push(u); 
	}
	while (sz(q)) {
		int u = q.front(); q.pop();
		topsort.pb(u);
		for (auto &v : adj_ABC_rev[u]) {
			outdeg_ABC[v]--;
			if (outdeg_ABC[v] == 0) {
				q.push(v);
			}
		}
	}
	if (sz(topsort) < 3*N) return -1;
	int res{};
	for (int i = 0; i <= K; i++) {
		for (auto &u : topsort) {
			int ind = u/3, r = u%3;
			for (auto &v : adj_ABC[u]) {
				ckmax(dp[i][u], dp[i][v] + 1);
			}
			if (i) {
				for (auto &[nxt, ch] : adj[ind]) {
					int v = 3*nxt + r;
					ckmax(dp[i][u], dp[i-1][v]);
				}
			}
			dbg(dp[i][u], i, u);
		}
		ckmax(res, *max_element(dp[i], dp[i] + 3*N));
	}
	return res;
}
void solve() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		vector<pair<int, char>>().swap(adj[i]);
		vector<pair<int, char>>().swap(rev_adj[i]);
		for (int j = 0; j < 3; j++) {
			vi().swap(adj_ABC_rev[3*i + j]);
			vi().swap(adj_ABC[3*i + j]);
		}
	}
	for (int i = 0; i < M; i++) {
		int u, v; cin >> u >> v, u--, v--;
		char ch; cin >> ch;
		adj[u].pb({v, ch});
		rev_adj[v].pb({u, ch});
	}
	if (K == -1) {
		cout << calc_K_INF() << '\n';
		return;
	}
	construct_ABC_graph();
	int ans = check_ABC_cycle();
	cout << ans << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int testcase = 1;
	cin >> testcase;
	for (int tc = 1; tc <= testcase; tc++) {
		cout << "Case #" << tc << '\n';
		solve();
	}
}
