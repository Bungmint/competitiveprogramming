#include <bits/stdc++.h>

using namespace std;
const int MAX = 4003;
vector<int> adj[MAX];
bool vis[MAX];
int dist[MAX];
vector<pair<int, pair<int, int>>> triplets;
int min_sum = 12100;

void dfs(int x, int start, int from, int dist)
{
    if (vis[x])
        return;
    if (dist > 2)
        return;
    for (auto y : adj[x])
    {
        if (dist == 2 && y == start)
        {
            int popularity = adj[start].size() + adj[x].size() + adj[from].size() - 6;
            min_sum = min(min_sum, popularity);
        }
        dfs(y, start, x, dist + 1);
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++)
    {

        if (adj[i].size() < 2)
            continue;
        memset(vis, false, sizeof(vis));
        memset(dist, 0, sizeof(dist));
        dfs(i, i, 0, 0);
    }
    if (min_sum != 12100)
    {
        cout << min_sum << "\n";
    }
    else
    {
        cout << -1 << "\n";
    }
}