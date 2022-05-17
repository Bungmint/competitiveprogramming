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
const int N = 3e5 + 10, LOG = 20;
int up[N][LOG], minn[N][LOG], dep[N];
vector<pair<int, int>> adj[N];
void dfs(int v, int pv)
{
    for (auto &e : adj[v])
    {
        if (e.first != pv)
        {
            dep[e.first] = dep[v] + 1;
            up[e.first][0] = v;
            minn[e.first][0] = e.second;
            for (int i = 1; i < LOG; i++)
            {
                up[e.first][i] = up[up[e.first][i - 1]][i - 1];
                minn[e.first][i] = min(minn[up[e.first][i - 1]][i - 1], minn[e.first][i - 1]);
            }
            dfs(e.first, v);
        }
    }
}

int lca(int a, int b)
{
    if (dep[a] < dep[b])
        swap(a, b);
    int k = dep[a] - dep[b];
    for (int i = LOG - 1; i >= 0; i--)
    {
        if (k & (1 << i))
            a = up[a][i];
    }
    if (a == b)
        return a;
    for (int i = LOG - 1; i >= 0; i--)
    {
        if (up[a][i] != up[b][i])
        {
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}

int lift(int u, int x)
{
    int ans = INT_MAX;
    for (int i = LOG - 1; i >= 0; i--)
    {
        if ((1 << i) & x)
        {
            ans = min(ans, minn[u][i]);
            u = up[u][i];
        }
    }
    return ans;
}

void solve()
{
    int n, m, q;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].PB({v, w});
        adj[v].PB({u, w});
    }
    dfs(1, 0);
    cin >> q;
    while (q--)
    {
        int u, v, c;
        cin >> u >> v;
        c = lca(u, v);
        int seg1 = dep[u] - dep[c], seg2 = dep[v] - dep[c];
        int maxflow = INT32_MAX;
        if (seg1 != 0)
            maxflow = min(maxflow, lift(u, seg1));
        if (seg2 != 0)
            maxflow = min(maxflow, lift(v, seg2));
        cout << maxflow << "\n";
    }
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