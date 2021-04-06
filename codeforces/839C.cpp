#include <bits/stdc++.h>

using namespace std;
int total_leng = 0, total_ways = 0;
const int MAX = 1e5 + 7;
vector<int> adj[MAX];
using ld = long double;

ld dfs(int x, int parent)
{
    ld sum = 0;
    for (auto e : adj[x])
    {
        if (e != parent)
        {
            sum += dfs(e, x) + 1;
        }
    }
    if (sum == 0)
    {
        return sum;
    }
    else
    {
        if (parent == 0)
        {
            return sum / adj[x].size();
        }
    }
    return sum / (adj[x].size() - 1);
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cout << setprecision(15);
    cout << dfs(1, 0) << "\n";
    return 0;
}