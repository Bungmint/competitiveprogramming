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
const int N = 2e5 + 1, M = 4e5 + 1;
pair<int, int> query[M];
pair<pair<int, bool>, pair<int, bool>> monke[N];
int n, m, sz[N], p[N], l, r, mon, hand, ans[N], targ;
bool con1, con2;

int root(int a) { return ((a == p[a]) ? a : root(p[a])); }
void unite(int a, int b)
{
    a = root(a), b = root(b);
    if (a == b)
        return;
    if (sz[a] < sz[b])
        swap(a, b);
    p[b] = a, sz[a] += sz[b];
}
bool con(int a)
{
    return (root(a) == root(1));
}
int search(int a)
{
    while (ans[a] == -2)
        a = p[a];
    return ans[a];
}

void solve()
{
    cin >> n >> m;
    fill(ans + 1, ans + n + 1, -2);
    fill(sz + 1, sz + n + 1, 1);
    iota(p + 1, p + n + 1, 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> l >> r;
        monke[i].first = {l, true};
        monke[i].second = {r, true};
    }
    for (int i = 0; i < m; i++)
    {
        cin >> mon >> hand;
        query[i] = {mon, hand};
        if (hand == 1)
        {
            monke[mon].first.second = false;
        }
        else
        {
            monke[mon].second.second = false;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (monke[i].first.first != -1 && monke[i].first.second)
            unite(i, monke[i].first.first);
        if (monke[i].second.first != -1 && monke[i].second.second)
            unite(i, monke[i].second.first);
    }
    for (int i = 1; i <= n; i++)
        if (con(i))
            ans[i] = -1;
    for (int i = m - 1; i >= 0; i--)
    {
        mon = query[i].first, hand = query[i].second;
        targ = ((hand == 1) ? monke[mon].first.first : monke[mon].second.first);
        con1 = con(mon), con2 = con(targ);
        if (!con1 && con2)
        {
            ans[root(mon)] = i;
        }
        else if (con1 && !con2)
        {
            ans[root(targ)] = i;
        }
        unite(mon, targ);
    }
    for (int i = 1; i <= n; i++)
        cout << search(i) << "\n";
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