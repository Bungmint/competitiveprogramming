#include <bits/stdc++.h>
using namespace std;

#define pb push_back


const int N = 1e5+1;
const int INF = 1e9;
int miX, miY, maX, maY, x[N], y[N];
vector<int> G[N];
bool vis[N];

void setIO(string s){
	freopen((s+".in").c_str(), "r", stdin);
	freopen((s+".out").c_str(), "w", stdout);
}

void dfs(int v){
	vis[v] = 1;
	miX = min(miX, x[v]);
	miY = min(miY, y[v]);
	maX = max(maX, x[v]);
	maY = max(maY, y[v]);
	for (int e:G[v]){
		if (!vis[e]) dfs(e);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	setIO("fenceplan");
	int n, m;
	cin >> n>>m;
	for (int i=1;i<=n;++i){
		cin >> x[i]>>y[i];
	}
	for (int i=0;i<m;++i){
		int u, v;
		cin >> u >> v;
		G[u].pb(v);
		G[v].pb(u);
	}
	int ans = INF;
	for (int i=1;i<=n;++i){
		if (!vis[i]){
			miX = INF, miY = INF, maX = 0, maY = 0;
			dfs(i);
			ans = min(ans, (maX-miX)*2+(maY-miY)*2);
		}
	}
	cout << ans << "\n";
}