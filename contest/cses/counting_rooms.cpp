//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
const int MAX = 1001;
bool vis[MAX][MAX];
char maze[MAX][MAX];
int n, m;

void dfs(int x, int y)
{
    if (x < 0 || x >= n)
        return;
    if (y < 0 || y >= m)
        return;
    if (vis[x][y])
        return;
    if (maze[x][y] == '#')
        return;
    vis[x][y] = true;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y - 1);
    dfs(x, y + 1);
}

void solve()
{
    memset(vis, false, sizeof(vis));
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++)
        {
            maze[i][j] = s[j];
        }
    }
    int rooms = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (vis[i][j] || maze[i][j] == '#')
                continue;
            dfs(i, j);
            rooms++;
        }
    }
    cout << rooms << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}