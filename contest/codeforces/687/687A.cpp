#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;
vector<int> adj[MAX];
bool vis[MAX];
int color[MAX];
bool impossible = false;

void dfs(int x, int col)
{
    if (vis[x])
    {
        if (col != color[x])
            impossible = true;
        return;
    }
    vis[x] = true;
    color[x] = col;
    for (auto e : adj[x])
    {
        dfs(e, (col + 1) % 2);
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;
    memset(color, -1, sizeof(color));
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
    {
        if (vis[i])
            continue;
        dfs(i, 0);
    }
    if (impossible)
        cout << -1 << "\n";
    else
    {
        vector<int> a;
        vector<int> b;
        for (int i = 1; i <= n; i++)
        {
            assert(color[i] != -1);
            if (color[i] == 0)
                a.push_back(i);
            else
                b.push_back(i);
        }
        cout << a.size() << "\n";
        for (auto x : a)
        {
            cout << x << " ";
        }
        cout << "\n";
        cout << b.size() << "\n";
        for (auto x : b)
        {
            cout << x << " ";
        }
        cout << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}