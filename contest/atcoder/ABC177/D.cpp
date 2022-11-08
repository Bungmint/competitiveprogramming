#include <bits/stdc++.h>

using namespace std;
const int MAX = 2e5 + 7;
vector<int> adj[MAX];
bool vis[MAX];

void dfs(int x, int &counter)
{
    if (vis[x])
        return;
    vis[x] = true;
    counter++;
    for (auto y : adj[x])
    {
        dfs(y, counter);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int max_g = 0;
    for (int i = 1; i <= n; i++)
    {
        if (vis[i])
            continue;
        int count = 0;
        dfs(i, count);
        max_g = max(max_g, count);
    }
    cout << max_g << "\n";
    return 0;
}