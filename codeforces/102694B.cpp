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
const int N = 3e5 + 10;
vector<int> adj[N];
int dep[N], max_d = 0LL, n, vert;
bool ispos[N];
void dfs(int V, int pV)
{
    for (auto e : adj[V])
    {
        if (e != pV)
        {
            dep[e] = dep[V] + 1;
            if (dep[e] > max_d)
            {
                max_d = dep[e];
                vert = e;
            }
            dfs(e, V);
        }
    }
}

void dia()
{
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
    {
        if (dep[i] == max_d)
            ispos[i] = true;
    }
    max_d = 0;
    dep[vert] = 0;
    dfs(vert, 0);
    for (int i = 1; i <= n; i++)
    {
        if (dep[i] == max_d)
            ispos[i] = true;
    }
    int ans = max_d;
    for (int i = 1; i <= n; i++)
    {
        if (ispos[i])
            cout << ans + 1 << "\n";
        else
            cout << ans << "\n";
    }
}

void solve()
{
    cin >> n;
    if (n == 1)
    {
        cout << 1 << "\n";
        return;
    }
    if (n == 2)
    {
        int u, v;
        cin >> u >> v;
        cout << 2 << "\n"
             << 2 << "\n";
        return;
    }
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].PB(v);
        adj[v].PB(u);
    }
    dia();
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