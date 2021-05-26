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
const int N = 1001, M = 10001;
ar<ll, 3> Edge[M];
ll w;
int sz[N], p[N], n, m, u, v, cnt;

void prep()
{
    fill(sz + 1, sz + 1 + n, 1);
    iota(p + 1, p + n + 1, 1);
}
int root(int a) { return p[a] = ((a == p[a]) ? a : root(p[a])); }
void unite(int a, int b)
{
    a = root(a);
    b = root(b);
    if (a == b)
        return;
    if (sz[a] < sz[b])
        swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
}
bool same(int a, int b) { return root(a) == root(b); }

void solve()
{
    cin >> n >> m;
    prep();
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        Edge[i] = {w, u, v};
    }
    sort(Edge, Edge + m);
    ll ans, mi = Edge[0][0], ma;
    cnt = 0;
    for (int i = 0; i < m; i++)
    {
        u = Edge[i][1], v = Edge[i][2], w = Edge[i][0];
        if (same(u, v))
            continue;
        unite(u, v);
        cnt++;
        if (cnt == n - 1)
        {
            ma = w;
            break;
        }
    }
    if (cnt != n - 1)
    {
        cout << "NO"
             << "\n";
        return;
    }
    ans = llabs(ma - mi);
    for (int i = 0; i <= m; i++)
    {
        cnt = 0;
        prep();
        mi = Edge[i][0];
        for (int j = i; j < m; j++)
        {
            u = Edge[j][1], v = Edge[j][2], w = Edge[j][0];
            if (same(u, v))
                continue;
            unite(u, v);
            cnt++;
            if (cnt == n - 1)
            {
                ma = w;
                break;
            }
        }
        if (cnt != n - 1)
            break;
        ans = min(llabs(ma - mi), ans);
    }
    cout << "YES"
         << "\n";
    cout << ans << "\n";
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