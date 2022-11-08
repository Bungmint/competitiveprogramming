#pragma GCC optimize("Ofast") //uncomment to squeeze a O(n^2) method for 10^5 ish cases
#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
const int MAX = 2e5 + 5;
vector<int> adj[MAX];
int color[MAX];
int N;

void dfs(int V, int pV)
{
    N = max(N, 1 + (int)adj[V].size());
    for (auto v : adj[V])
    {
        if (v != pV)
            dfs(v, V);
    }
}

void coloring(int V, int pV)
{
    int colorV = color[V], colorpV = color[pV];
    int i = 0, c = 1;
    while (i < adj[V].size())
    {
        if (adj[V][i] == pV)
        {
            i++;
            continue;
        }
        else if (c == colorV || c == colorpV)
        {
            c++;
            continue;
        }
        int cur = adj[V][i];
        color[cur] = c;
        c++;
        i++;
        coloring(cur, V);
    }
}

void solve()
{
    int n;
    cin >> n;
    N = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    color[0] = 0;
    color[1] = 1;
    coloring(1, 0);
    cout << N << "\n";
    for (int i = 1; i <= n; i++)
    {
        cout << color[i] << " ";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}