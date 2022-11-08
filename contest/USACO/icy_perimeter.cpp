#include <bits/stdc++.h>
using namespace std;
bool grid[1000][1000];
int dx[4] = {0,0,-1, 1}, dy[4] = {-1,1,0,0}, n;
bool vis[1000][1000];
int cnt = 0, per = 0;

bool good(int newX, int newY){
	return newX>=0&&newX<n&&newY<n&&newY>=0;
}

void dfs(int x, int y){
	cnt++;
	vis[x][y] = 1;
	int val = 0;
	for (int i=0;i<4;++i){
		int newX = x + dx[i], newY = y + dy[i];
		if (good(newX, newY)&&grid[newX][newY]&&!vis[newX][newY]){
			dfs(newX, newY);
		}else{
			if (!good(newX, newY)) val++;
			else if(!grid[newX][newY]) val++;
		}
	}
	per += val;
}

void setIO(string s){
	freopen((s+".in").c_str(), "r", stdin);
	freopen((s+".out").c_str(), "w", stdout);
}

void solve(){
	cin >> n;
	for (int i=0;i<n;++i){
		string s;
		cin >> s;
		for (int j=0;j<n;++j){if (s[j]=='#') grid[i][j]=1;}
	}
	int area = 0, ans = 0;
	for (int i=0;i<n;++i){
		for (int j=0;j<n;++j){
			if (grid[i][j]&&!vis[i][j]){
				cnt = 0; per = 0;
				dfs(i, j);
				if (area<cnt){
					area = cnt;
					ans = per;
				}else if (area==cnt){
					ans = min(per, ans);
				}
			}
		}
	}
	cout << area << " "<< ans << "\n";
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	setIO("perimeter");
	solve();
}