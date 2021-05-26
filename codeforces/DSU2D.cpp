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
const int N = 3e5 + 1;
int n, q, sz[N], p[N], dist[N], op, a, b, c, root;

int get(int x)
{
    if (x == p[x])
    {
        dist[x] = 0;
        return x;
    }
    root = get(p[x]);
    dist[x] += dist[p[x]];
    return p[x] = root;
}

void solve()
{
    cin >> n >> q;
    iota(p, p + n, 0);
    fill(sz, sz + n, 1);
    fill(dist, dist + n, 0);
    while (q--)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> b >> a;
            a--;
            b--;
            p[b] = a;
            dist[b] = 1;
        }
        else
        {
            cin >> c;
            c--;
            get(c);
            cout << dist[c] << "\n";
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