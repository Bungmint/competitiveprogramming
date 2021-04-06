#include <bits/stdc++.h>

using namespace std;
vector<int> adj[500];
vector<int> reverse_adj[500];
bool vis[500];
stack<int> st;

void dfs(int x, const vector<int> adjacent[], bool push_stack)
{
    if (vis[x])
        return;
    vis[x] = true;
    for (auto e : adjacent[x])
    {
        dfs(e, adjacent, push_stack);
        if (push_stack)
            st.push(e);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    string h, v;
    cin >> h >> v;
    for (int i = 0; i <= n - 1; i++)
    {
        if (h[i] == '>')
        {
            for (int j = 0; j < m - 1; j++)
            {
                adj[i * m + j].push_back(i * m + j + 1);
                reverse_adj[i * m + j + 1].push_back(i * m + j);
            }
        }
        else
        {
            for (int j = 0; j < m - 1; j++)
            {
                adj[i * m + j + 1].push_back(i * m + j);
                reverse_adj[i * m + j].push_back(i * m + j + 1);
            }
        }
    }
    for (int i = 0; i <= m - 1; i++)
    {
        if (v[i] == 'v')
        {
            for (int j = 0; j < n; j++)
            {
                adj[i + j * m].push_back(i + (j + 1) * m);
                reverse_adj[i + (j + 1) * m].push_back(i + j * m);
            }
        }
        else
        {
            for (int j = 0; j < n; j++)
            {
                reverse_adj[i + j * m].push_back(i + (j + 1) * m);
                adj[i + (j + 1) * m].push_back(i + j * m);
            }
        }
    }
    dfs(0, adj, true);
    bool is_pos = true;
    for (int i = 0; i < n * m; i++)
    {
        if (!vis[i])
            is_pos = false;
    }
    while (!st.empty())
    {
        int e = st.top();
        st.pop();
        memset(vis, false, sizeof(vis));
        dfs(e, reverse_adj, false);
        for (int i = 0; i < n * m; i++)
        {
            if (!vis[i])
                is_pos = false;
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
    return 0;
}