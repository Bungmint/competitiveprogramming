#include <bits/stdc++.h>

using namespace std;
const int MAX = 405;
vector<int> adj_train[MAX];
vector<int> adj_bus[MAX];
unordered_set<int> train[MAX];
int dist[MAX];
bool vis[MAX];

void bfs(int x, const vector<int> adjacent[])
{
    queue<int> q;
    q.push(x);
    dist[x] = 0;
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (auto y : adjacent[cur])
        {
            if (!vis[y])
            {
                vis[y] = true;
                q.push(y);
                dist[y] = dist[cur] + 1;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj_train[u].push_back(v);
        adj_train[v].push_back(u);
        train[u].insert(v);
        train[v].insert(u);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (train[i].count(j) == 0 && i != j)
            {
                adj_bus[i].push_back(j);
            }
        }
    }
    bfs(1, adj_bus);
    int bt = dist[n];
    memset(vis, false, sizeof(vis));
    memset(dist, 0, sizeof(dist));
    bfs(1, adj_train);
    int tt = dist[n];
    if (bt && tt)
    {
        cout << max(bt, tt) << "\n";
    }
    else
    {
        cout << -1 << "\n";
    }
    return 0;
}