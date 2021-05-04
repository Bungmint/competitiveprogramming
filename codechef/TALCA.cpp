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
const int MAX = 2e5 + 5, LOG = 20;
vector<int> adj[MAX];
int up[MAX][LOG];
int depth[MAX];

void dfs(int V, int pV)
{
    for (auto e : adj[V])
    {
        if (e == pV)
            continue;
        depth[e] = depth[V] + 1;
        up[e][0] = V;
        for (int i = 1; i < LOG; i++)
            up[e][i] = up[up[e][i - 1]][i - 1];
        dfs(e, V);
    }
}

int lca(int a, int b)
{
    if (depth[a] < depth[b])
        swap(a, b);
    int k = depth[a] - depth[b];
    for (int i = LOG - 1; i >= 0; i--)
    {
        if ((1 << i) & k)
        {
            a = up[a][i];
        }
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

int modi_lca(int r, int a, int b)
{
    if (depth[a] < depth[b])
        swap(a, b);
    int u = lca(r, a), v = lca(a, b), w = lca(r, b);
    if (depth[u] <= depth[v] && depth[w] <= depth[v])
        return v;
    if (u == a && a != v)
    {
        return a;
    }
    if (w == b && b != v)
    {
        return b;
    }
    if (depth[u] > depth[v])
    {
        return u;
    }
    if (depth[w] > depth[v])
    {
        return w;
    }
    return r;
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].PB(v);
        adj[v].PB(u);
    }
    dfs(1, 0);
    int q;
    cin >> q;
    while (q--)
    {
        int r, a, b;
        cin >> r >> a >> b;
        cout << modi_lca(r, a, b) << "\n";
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