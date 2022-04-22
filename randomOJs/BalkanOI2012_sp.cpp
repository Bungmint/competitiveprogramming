#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Edge {
	int u, v;
	ll c;
} edges[200000];

bool operator<(Edge a, Edge b) {
	if (a.c == b.c) {
		if (a.u == b.u) return a.v < b.v;
		return a.u < b.u;
	}
	return a.c < b.c;
}

vector<pair<int, ll>> graph[2001];
vector<int> sp_tree[2001];
int sp[2001], lca[2001];
ll from_a[2001], from_b[2001], ans[2001];
int par[2001], depth[2001];

void dijkstra(int source, ll *dist) {
	priority_queue<tuple<ll, int, int>> pq;
	pq.push({-1, source, 0});
	while (pq.size()) {
		int curr, parent;
		ll cost;
		tie(cost, curr, parent) = pq.top();
		pq.pop();
		if (!dist[curr]) {
			par[curr] = parent;
			dist[curr] = -cost;
			for (pair<int, ll> i : graph[curr])
				pq.push({cost - i.second, i.first, curr});
		}
	}
}

void dfs(int node) {
	for (int i : sp_tree[node]) {
		depth[i] = depth[node] + 1;
		dfs(i);
	}
}

int find_lca(int a, int b) {
	while (depth[a] > depth[b]) a = par[b];
	while (depth[b] > depth[a]) b = par[b];
	while (a != b) a = par[a], b = par[b];
	return a;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m, a, b, k;
	cin >> n >> m >> a >> b;
	for (int i = 0; i < m; i++) {
		cin >> edges[i].u >> edges[i].v >> edges[i].c;
		edges[i + m] = {edges[i].v, edges[i].u, edges[i].c};
		graph[edges[i].u].push_back({edges[i].v, edges[i].c});
		graph[edges[i].v].push_back({edges[i].u, edges[i].c});
	}

	dijkstra(b, from_b);
	dijkstra(a, from_a);

	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> sp[i];
		if (i) par[sp[i]] = sp[i - 1];
	}

	for (int i = 1; i <= n; i++)
		if (par[i]) sp_tree[par[i]].push_back(i);
	dfs(a);
	for (int i = 1; i <= n; i++)
		lca[i] = find_lca(i, b);

	memset(ans, 0x3f, sizeof(ans));
	for (int i = 0; i < 2 * m; i++) {
		if (par[edges[i].u] == edges[i].v || par[edges[i].v] == edges[i].u) continue;
		int x = find(sp, sp + k, lca[edges[i].u]) - sp;
		int y = find(sp, sp + k, lca[edges[i].v]) - sp;
		for (int j = x; j < y; j++)
			ans[j] = min(ans[j], from_a[edges[i].u] + from_b[edges[i].v] + edges[i].c - 2);
	}

	for (int i = 0; i < k - 1; i++)
		cout << (ans[i] == 0x3f3f3f3f3f3f3f3f ? -1 : ans[i]) << '\n';
	return 0;
}