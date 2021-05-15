//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7; //998244353
const int N = 1e5 + 5;
const ll rev2 = 5e8 + 4;
vector<vector<int>> adj;
ll ans = 0LL;
ll dp[N][2];

void dfs(int V, int pV)
{
    ll temp = 0LL;
    dp[V][0] = 1LL;
    dp[V][1] = 0LL;
    for (auto e : adj[V])
    {
        if (e != pV)
        {
            dfs(e, V);
            temp = (temp + (dp[e][0] * dp[e][0]) % MOD) % MOD;
            dp[V][0] = (2 * dp[e][0] + dp[V][0]) % MOD;
        }
    }
    ll sum = (((dp[V][0] - 1 + MOD) % MOD) * rev2) % MOD;
    dp[V][1] = (((sum * sum) % MOD) - temp + MOD) % MOD;
    ans = (dp[V][1] + ans) % MOD;
}

void solve()
{
    adj.clear();
    int n;
    cin >> n;
    adj.resize(n + 1);
    memset(dp, 0, sizeof(dp));
    ans = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].PB(v);
        adj[v].PB(u);
    }
    dfs(1, 0);
    cout << (ans + dp[1][0]) % MOD << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}