#include <bits/stdc++.h>

using namespace std;
const int MAX = 1e5 + 7;
bool vis[MAX];

vector<int> sieve(int num)
{
    vector<bool> A(num + 1, true);
    vector<int> res;
    A[0] = false, A[1] = false;

    for (int i = 2; i * i <= num; i++)
    {
        if (A[i])
        {
            for (int j = i * i; j <= num; j += i)
            {
                A[j] = false;
            }
        }
    }
    for (int i = 0; i <= num; i++)
    {
        if (A[i])
        {
            res.push_back(i);
        }
    }
    return res;
}

void dfs_count(int x, int &counter, const vector<vector<int>> &adjacent)
{
    if (vis[x])
        return;
    vis[x] = true;
    counter++;
    for (auto y : adjacent[x])
    {
        dfs_count(y, counter, adjacent);
    }
}

int main()
{
    vector<int> primes = sieve(2e6);
    int t;
    cin >> t;
    while (t--)
    {
        memset(vis, false, sizeof(vis));
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj(n + 1);
        for (int i = 1; i <= m; i++)
        {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        int maximal = -1;
        for (int i = 1; i <= n; i++)
        {
            if (vis[i])
            {
                continue;
            }
            else if (adj[i].size() == 0)
            {
                continue;
            }
            int counter = 0;
            dfs_count(i, counter, adj);
            maximal = max(maximal, counter);
        }
        if (maximal == -1)
        {
            cout << maximal << "\n";
        }
        else
        {
            cout << primes[maximal - 1] << "\n";
        }
    }
    return 0;
}