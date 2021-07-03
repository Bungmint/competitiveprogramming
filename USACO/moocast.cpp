#include <bits/stdc++.h>
using namespace std;

const int MN = 200;
int x[MN], y[MN], p[MN],n;
bool vis[MN];

void setIO(string s){
	freopen((s+".in").c_str(), "r", stdin);
	freopen((s+".out").c_str(), "w", stdout);
}

int dif(int i, int j){
	return (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);
}

void dfs(int x){
	vis[x] = 1;
	for (int i=0;i<n;++i){
		if (!vis[i]&&dif(i, x)<=p[x]*p[x]){
			dfs(i);
		}
	}
}

void solve(){
	cin >> n;
	for (int i=0;i<n;++i){
		cin >> x[i] >> y[i] >> p[i];
	}
	int ans = 0;
	for (int i=0;i<n;++i){
		memset(vis, 0, sizeof(vis));
		dfs(i);
		int cnt = 0;
		for (int i=0;i<n;++i){
			if (vis[i]) cnt++;
		}
		ans = max(ans, cnt);
	}
	cout << ans << "\n";
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	setIO("moocast");
	solve();
}