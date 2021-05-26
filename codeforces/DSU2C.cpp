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
const int N = 200001;
int n, q, sz[N], p[N], op, x, y, de;
set<int> s1;

int root(int a)
{
    return p[a] = ((p[a] == a) ? a : root(p[a]));
}
void unite(int a, int b)
{
    a = root(a), b = root(b);
    if (a == b)
        return;
    if (sz[a] < sz[b])
        swap(a, b);
    sz[a] += sz[b];
    p[b] = a;
}

void solve()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        s1.insert(i);
        p[i] = i;
        sz[i] = 1;
    }
    while (q--)
    {
        cin >> op >> x >> y;
        if (op == 1)
        {
            unite(x, y);
        }
        else if (op == 2)
        {
            while (*s1.lower_bound(x) < y)
            {
                de = *s1.lower_bound(x);
                unite(de + 1, x);
                s1.erase(de);
            }
        }
        else
        {
            cout << ((root(x) == root(y)) ? "YES" : "NO") << "\n";
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