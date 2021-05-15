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
int up[N][LOG], dep[N];
vector<int> adj[N];
void dfs(int V, int pV)
{
    for (auto e : adj[V])
    {
        if (e != pV)
        {
            dep[e] = dep[V] + 1;
            up[e][0] = V;
            for (int i = 1; i < LOG; i++)
            {
                up[e][i] = up[up[e][i - 1]][i - 1];
            }
            dfs(e, V);
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

int lift(int v, int a)
{
    for (int i = LOG - 1; i >= 0; i--)
    {
        if ((1 << i) & a)
            v = up[v][i];
    }
    return v;
}

void solve()
{
    int n, q;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].PB(v);
        adj[v].PB(u);
    }
    cin >> q;
    dfs(1, 0);
    while (q--)
    {
        int u, v, c;
        cin >> u >> v >> c;
        int low = lca(u, v);
        int seg1 = dep[u] - dep[low], seg2 = dep[v] - dep[low];
        if (seg1 + seg2 <= c)
            cout << v << "\n";
        else if (c > seg1)
        {
            c -= seg1;
            seg2 -= c;
            cout << lift(v, seg2) << "\n";
        }
        else
        {
            cout << lift(u, c) << "\n";
        }
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