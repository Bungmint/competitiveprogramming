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
const int N = 2e5 + 10;
const int LOG = 20;
int up[N][LOG];
int dep[N];
vector<int> adj[N];

void dfs(int v, int pV)
{
    for (auto e : adj[v])
    {
        if (e == pV)
            continue;
        dep[e] = dep[v] + 1;
        up[e][0] = v;
        for (int i = 1; i < LOG; i++)
        {
            up[e][i] = up[up[e][i - 1]][i - 1];
        }
        dfs(e, v);
    }
}
int lca(int a, int b)
{
    if (dep[a] < dep[b])
        swap(a, b);
    int k = dep[a] - dep[b];
    for (int j = LOG - 1; j >= 0; j--)
    {
        if ((1 << j) & k)
        {
            a = up[a][j];
        }
    }
    if (a == b)
        return a;
    for (int j = LOG - 1; j >= 0; j--)
    {
        if (up[a][j] != up[b][j])
        {
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0];
}

void solve()
{
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].PB(v);
        adj[v].PB(u);
    }
    dfs(1, 0);
    while (q--)
    {
        int a, b, c;
        cin >> a >> b;
        c = lca(a, b);
        cout << dep[a] + dep[b] - 2 * dep[c] << "\n";
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