#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
int N;
bool vis[11][11][11];
char par[11][11][11];
int k, n, m;

void dfs(int x, int y, int h)
{
    if (h >= k || x >= n || y >= m || h < 0 || x < 0 || y < 0)
        return;
    if (vis[h][x][y])
        return;
    if (par[h][x][y] == '#')
        return;
    N++;
    vis[h][x][y] = true;
    dfs(x + 1, y, h);
    dfs(x - 1, y, h);
    dfs(x, y - 1, h);
    dfs(x, y + 1, h);
    dfs(x, y, h + 1);
    dfs(x, y, h - 1);
}

void solve()
{

    cin >> k >> n >> m;
    N = 0;
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            string s;
            cin >> s;
            for (int l = 0; l < m; l++)
            {
                par[i][j][l] = s[l];
            }
        }
    }
    int x, y;
    cin >> x >> y;
    dfs(x - 1, y - 1, 0);
    cout << N << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}