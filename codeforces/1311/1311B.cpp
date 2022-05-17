#include <bits/stdc++.h>

using namespace std;
#define all(v) (v).begin()(v).end()
const int MAX = 107;
bool vis[MAX];

void dfs(int x, const vector<vector<int>> &adjacent)
{
    if (vis[x])
        return;
    vis[x] = true;
    for (auto y : adjacent[x])
    {
        dfs(y, adjacent);
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> arr(n + 1);
        vector<vector<int>> adj(n + 1);
        for (int i = 1; i <= n; i++)
        {
            cin >> arr[i].first;
            arr[i].second = i;
        }
        for (int i = 0; i < m; i++)
        {
            int p;
            cin >> p;
            adj[p].push_back(p + 1);
            adj[p + 1].push_back(p);
        }
        sort(1 + arr.begin(), arr.end());
        bool is_pos = true;
        for (int i = 1; i <= n; i++)
        {
            memset(vis, false, sizeof(vis));
            dfs(arr[i].second, adj);
            if (!vis[i])
            {
                is_pos = false;
                break;
            }
        }
        if (is_pos)
        {
            cout << "YES"
                 << "\n";
        }
        else
        {
            cout << "NO"
                 << "\n";
        }
    }
}