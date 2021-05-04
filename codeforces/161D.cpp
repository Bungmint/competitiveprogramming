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
vector<int> adj[50001];
int dp[50001][501];
int n, k;
ll ans = 0;

void dfs(int V, int pV)
{
    dp[V][0] = 1;
    for (auto e : adj[V])
    {
        if (e == pV)
            continue;
        dfs(e, V);
        for (int i = 0; i < k; i++)
        {
            dp[V][i + 1] += dp[e][i];
        }
    }
    ans += dp[V][k];
    ll val = 0;
    for (auto e : adj[V])
    {
        if (e == pV)
            continue;

        for (int i = 1; i <= k - 1; i++)
        {
            val += dp[e][i - 1] * (dp[V][k - i] - dp[e][k - i - 1]);
        }
    }
    ans += val / 2;
}

void solve()
{

    cin >> n >> k;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].PB(v);
        adj[v].PB(u);
    }
    dfs(1, 0);
    cout << ans << "\n";
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