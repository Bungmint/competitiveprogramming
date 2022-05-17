//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
const int MAX = 2e5 + 5;
vector<pair<int, bool>> adj[MAX];
int dp[MAX];

int dfs(int V, int pV)
{
    int ans = 0;
    for (auto e : adj[V])
    {
        if (e.first == pV)
            continue;
        ans += dfs(e.first, V);
        if (!e.second)
            ans++;
    }
    return ans;
}
void dpd(int V, int pV)
{
    for (auto e : adj[V])
    {
        if (e.first == pV)
            continue;
        dp[e.first] = dp[V];
        if (e.second)
            dp[e.first]++;
        else
            dp[e.first]--;
        dpd(e.first, V);
    }
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].PB({v, true});
        adj[v].PB({u, false});
    }
    dp[1] = dfs(1, 0);
    dpd(1, 0);
    int m = INF;
    for (int i = 1; i <= n; i++)
    {
        m = min(m, dp[i]);
    }
    cout << m << "\n";
    for (int i = 1; i <= n; i++)
    {
        if (dp[i] == m)
            cout << i << " ";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}