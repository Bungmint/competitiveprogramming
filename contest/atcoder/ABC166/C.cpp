#include <bits/stdc++.h>
const int MAX = 1e5 + 5;
using namespace std;
vector<int> adj[MAX];
int heights[MAX];
bool visited[MAX];
int total = 0;

void btech_dfs(int x)
{
    if (visited[x])
        return;
    visited[x] = true;
    bool is_higher = true;
    for (auto y : adj[x])
    {
        if (heights[x] <= heights[y])
        {
            is_higher = false;
        }
        btech_dfs(y);
    }
    if (is_higher)
        total++;
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int tmp;
        cin >> tmp;
        heights[i] = tmp;
    }
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++)
    {
        btech_dfs(i);
    }
    cout << total << "\n";
    return 0;
}