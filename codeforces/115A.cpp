#include <bits/stdc++.h>

using namespace std;
const int MAX = 2001;
int adj[MAX];
int dfs(int x)
{
    if (adj[x] == -1)
        return 1;
    return dfs(adj[x]) + 1;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> adj[i];
    }
    int max_chain = 0;
    for (int i = 1; i <= n; i++)
    {
        max_chain = max(max_chain, dfs(i));
    }
    cout << max_chain << "\n";
    return 0;
}