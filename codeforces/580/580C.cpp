#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
const int MAX = 1e5 + 10;
vector<int> adj[MAX];
int N;
int arr[MAX];
int n, m;

void dfs(int V, int pV, int cats)
{
    if (arr[V] && arr[pV])
        cats++;
    else
        cats = arr[V];
    if (cats > m)
        return;
    if (adj[V].size() == 1 && V != 1)
        N++;
    for (auto x : adj[V])
    {
        if (x != pV)
            dfs(x, V, cats);
    }
}

void solve()
{
    cin >> n >> m;
    N = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1, 0, 0);
    cout << N << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}