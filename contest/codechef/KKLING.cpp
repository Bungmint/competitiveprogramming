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
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353
const int N = 2e5 + 10, LOG = 20;
vector<vector<int>> adj, children;
int n, dp[N], ans[N], yo = 0;

void searchin(int V, int pV, int root, int targ)
{
    if (dp[V] < targ)
        return;
    if (dp[V] == targ)
    {
        children[root].PB(V);
        bool sm = true;
        for (auto e : adj[V])
            if (dp[e] != dp[V] - 1)
                sm = false;
        if (sm)
        {
            for (auto e : adj[V])
                if (e != pV)
                    searchin(e, V, V, dp[V] - 1);
        }
        else
        {
            for (auto e : adj[V])
                if (e != pV && dp[e] != dp[V] - 2)
                    searchin(e, V, V, dp[V] - 1);
        }
        return;
    }
    if (V == 1)
    {
        for (auto e : adj[V])
            if (e != pV && dp[e] == dp[V] - 1)
                searchin(e, V, V, dp[V] - 1);
        return;
    }
    for (auto e : adj[V])
    {
        if (e != pV)
            searchin(e, V, root, targ);
    }
}

void dfs(int V, int pV)
{
    int time = 0LL;
    int fast_time = INF, cnt = 0;
    for (auto &e : adj[V])
    {
        if (e != pV)
        {
            dfs(e, V);
            if (fast_time > 1 + dp[e])
            {
                fast_time = 1 + dp[e];
                cnt = 1;
            }
            else if (fast_time == 1 + dp[e])
            {
                cnt++;
            }
        }
    }
    if (fast_time != INF && V != 1)
    {
        if (cnt != (int)adj[V].size() - 1)
        {
            time = fast_time + 1;
        }
        else
        {
            time = fast_time;
        }
    }
    else if (V == 1)
    {
        time = fast_time;
    }
    dp[V] = time;
}

void dfsch(int V)
{
    if ((int)children[V].size() == 0)
    {
        ans[yo] = V;
        yo++;
        return;
    }
    for (auto e : children[V])
    {
        dfsch(e);
    }
}

void solve()
{
    cin >> n;
    adj.clear();
    adj.resize(n + 1);
    children.clear();
    children.resize(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].PB(v);
        adj[v].PB(u);
    }
    dfs(1, 0);
    yo = 0;
    searchin(1, 0, 1, 0);
    dfsch(1);
    cout << yo << " " << dp[1] << "\n";
    sort(ans, ans + yo);
    for (int i = 0; i < yo; i++)
    {
        cout << ans[i] << " ";
    }
    cout << "\n";
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