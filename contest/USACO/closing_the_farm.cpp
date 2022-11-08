#include <bits/stdc++.h>
using namespace std;

#define pb push_back

vector<int> G[3001];
bool vis[3001];
set<int> forb;

void setIO(string s){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	freopen((s+".in").c_str(), "r", stdin);
	freopen((s+".out").c_str(), "w", stdout);
}

void dfs(int V){
	if (vis[V]) return;
	vis[V] = 1;
	for (int x:G[V]){
		if (forb.count(x)){
			continue;
		}
		dfs(x);
	}
}

int main(){
	setIO("closing");
	int n, m;
	cin >> n >> m;
	for (int i=0;i<m;++i){
		int u,v;
		cin>> u >> v;
		G[u].pb(v);
		G[v].pb(u);
	}
	vector<int> a(n);
	for (int i=0;i<n;++i){
		cin >> a[i];
	}
	dfs(1);
	bool ok = 1;
	for (int i=1;i<=n;++i){
		if (!vis[i]) ok = 0;
	}
	cout << (ok? "YES": "NO")<<"\n";
	for (int i=0;i<n;++i){
		if (i==n-1){
			break;
		}
		forb.insert(a[i]);
		memset(vis, 0, sizeof(vis));
		int st = a[i+1];
		dfs(st);
		ok = 1;
		for (int j=1;j<=n;++j){
			if (!forb.count(j)&&!vis[j]) ok = 0;
		}
		cout << (ok? "YES": "NO")<<"\n";
	}
	return 0;
}