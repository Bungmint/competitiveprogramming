#include <bits/stdc++.h>

using namespace std;
vector<int> adj[57];
bool vis[57];

void dfs(int x, int &counter)
{
    if (vis[x])
        return;
    vis[x] = true;
    counter++;
    for (auto e : adj[x])
    {
        dfs(e, counter);
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
    long long danger = 0LL;
    for (int i = 1; i <= n; i++)
    {
        if (vis[i])
            continue;
        int counter = 0;
        dfs(i, counter);
        assert(counter > 0);
        danger += counter - 1;
    }
    long long res = (1LL) << danger;
    cout << res << "\n";
    return 0;
}