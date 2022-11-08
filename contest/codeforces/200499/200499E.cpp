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
const int N = 1e5 + 1;
int sz[N], par[N], loc[N], n, q, s, t, u, v;

int root(int V)
{
    while (par[V] != V)
        V = par[V];
    return V;
}
void unite(int a, int b)
{
    a = root(a);
    b = root(b);
    if (a == 0 || b == 0)
        return;
    if (a != b)
    {
        if (sz[a] < sz[b])
            swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
    }
}

void solve()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        sz[i] = 1;
        loc[i] = i;
        par[i] = i;
    }
    while (q--)
    {
        cin >> s >> t;
        u = loc[s], v = loc[t];
        unite(u, v);
        loc[s] = 0;
        loc[t] = root(u);
    }
    unordered_map<int, int, custom_hash> m1;
    for (int i = 1; i <= n; i++)
    {
        if (loc[i] == 0)
            continue;
        m1[loc[i]] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        cout << m1[root(i)] << " ";
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