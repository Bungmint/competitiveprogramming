#include <bits/stdc++.h>

using namespace std;
const int MAX = 10010;
vector<int> adj[MAX];
int N;
bool vis[MAX];
int max_dp[MAX][3];
int min_dp[MAX][3];

void read_tree(string &treee)
{
    int n = N;
    char c = treee[n];
    if (c == '1')
    {
        N++;
        adj[n].push_back(N);
        read_tree(treee);
    }
    else if (c == '2')
    {
        N++;
        adj[n].push_back(N);
        read_tree(treee);
        adj[n].push_back(N);
        read_tree(treee);
    }
    else
    {
        N++;
    }
}

void dfs(int node)
{
    if (vis[node])
        return;
    vis[node] = true;
    if (adj[node].size() == 0)
    {
        max_dp[node][0] = 1;
        max_dp[node][1] = 0;
        max_dp[node][2] = 0;
        min_dp[node][0] = 1;
        min_dp[node][1] = 0;
        min_dp[node][2] = 0;
        return;
    }
    dfs(adj[node][0]);
    if (adj[node].size() == 1)
    {
        int node1 = adj[node][0];
        max_dp[node][0] = 1 + max(max_dp[node1][1], max_dp[node1][2]);
        max_dp[node][1] = max(max_dp[node1][0], max_dp[node1][2]);
        max_dp[node][2] = max(max_dp[node1][0], max_dp[node1][1]);
        min_dp[node][0] = 1 + min(min_dp[node1][1], min_dp[node1][2]);
        min_dp[node][1] = min(min_dp[node1][0], min_dp[node1][2]);
        min_dp[node][2] = min(min_dp[node1][0], min_dp[node1][1]);
    }
    else
    {
        dfs(adj[node][1]);
        int node1 = adj[node][0], node2 = adj[node][1];
        max_dp[node][0] = 1 + max(max_dp[node1][1] + max_dp[node2][2], max_dp[node1][2] + max_dp[node2][1]);
        max_dp[node][1] = max(max_dp[node1][0] + max_dp[node2][2], max_dp[node1][2] + max_dp[node2][0]);
        max_dp[node][2] = max(max_dp[node1][0] + max_dp[node2][1], max_dp[node1][1] + max_dp[node2][0]);
        min_dp[node][0] = 1 + min(min_dp[node1][1] + min_dp[node2][2], min_dp[node1][2] + min_dp[node2][1]);
        min_dp[node][1] = min(min_dp[node1][0] + min_dp[node2][2], min_dp[node1][2] + min_dp[node2][0]);
        min_dp[node][2] = min(min_dp[node1][0] + min_dp[node2][1], min_dp[node1][1] + min_dp[node2][0]);
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        string s;
        cin >> s;
        N = 0;
        read_tree(s);
        memset(vis, false, sizeof(vis));
        dfs(0);
        int max_g = max(max(max_dp[0][0], max_dp[0][1]), max_dp[0][2]);
        int min_g = min(min(min_dp[0][0], min_dp[0][1]), min_dp[0][2]);
        cout << max_g << " " << min_g << "\n";
    }
    return 0;
}