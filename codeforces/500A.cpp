#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
bool vis[30007];
int arr[30007];

void dfs(int x)
{
    if (vis[x])
        return;
    vis[x] = true;
    dfs(x + arr[x]);
}

void solve()
{
    int n, t;
    cin >> n >> t;
    for (int i = 1; i <= n - 1; i++)
    {
        cin >> arr[i];
    }
    dfs(1);
    if (vis[t])
        cout << "YES"
             << "\n";
    else
        cout << "NO"
             << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}