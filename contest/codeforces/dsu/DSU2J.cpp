#pragma GCC optimize("O3")
#pragma GCC target("sse4")
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
const int N = 3e5 + 1;
int sz[N], p[N], n, q, bi[N], u, v, root, a1, b1;

int get(int a)
{
    if (a == p[a])
    {
        bi[a] = 0;
        return a;
    }
    root = get(p[a]);
    bi[a] ^= bi[p[a]];
    return p[a] = root;
}
void unite(int a, int b)
{
    a1 = a, b1 = b;
    a = get(a), b = get(b);
    if (a == b)
        return;
    if (sz[a] < sz[b])
        swap(a, b);
    sz[a] += sz[b];
    p[b] = a;
    bi[b] = bi[a1] ^ bi[b1] ^ 1;
}

void solve()
{
    cin >> n >> q;
    fill(sz, sz + n, 1);
    iota(p, p + n, 0);
    for (int i = 1; i <= q; i++)
    {
        cin >> u >> v;
        u--;
        v--;
        if (get(u) != get(v))
            unite(u, v);
        else
        {
            if (bi[u] == bi[v])
            {
                cout << i << "\n";
                return;
            }
        }
    }
    cout << -1 << "\n";
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