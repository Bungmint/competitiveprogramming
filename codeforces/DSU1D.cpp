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
const int N = 50001, K = 150000;
ar<int, 3> query[K];
int sz[N], p[N], n, m, k, u, v, ans[K];
string op;

int root(int a)
{
    return (a == p[a] ? a : root(p[a]));
}

void unite(int a, int b)
{
    a = root(a);
    b = root(b);
    if (a == b)
        return;
    if (sz[a] < sz[b])
        swap(a, b);
    sz[a] += sz[b];
    p[b] = a;
}

void solve()
{
    cin >> n >> m >> k;
    iota(p + 1, p + n + 1, 1);
    fill(sz + 1, sz + n + 1, 1);
    while (m--)
        cin >> u >> v;
    for (int i = 0; i < k; i++)
    {
        cin >> op;
        cin >> u >> v;
        if (op == "cut")
        {
            query[i] = {0, u, v};
        }
        else
            query[i] = {1, u, v};
    }
    for (int i = k - 1; i >= 0; i--)
    {
        u = query[i][1], v = query[i][2];
        if (query[i][0] == 0)
        {
            unite(u, v);
        }
        else
        {
            ans[i] = ((root(u) == root(v)) ? 1 : 2);
        }
    }
    for (int i = 0; i < k; i++)
    {
        if (ans[i] == 1)
            cout << "YES"
                 << "\n";
        else if (ans[i] == 2)
            cout << "NO"
                 << "\n";
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