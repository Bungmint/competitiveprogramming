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
const int N = 2e5 + 1, LOG = 20;
vector<int> adj[N];
unordered_map<int, vector<int>, custom_hash> m1;
int n, dep[N], u, v, d, st[N], en[N], timer = 0;

void dfs(int V, int pV)
{
    st[V] = timer;
    m1[dep[V]].PB(st[V]);
    for (auto &e : adj[V])
    {
        if (e == pV)
            continue;
        timer++;
        dep[e] = dep[V] + 1;
        dfs(e, V);
    }
    en[V] = timer;
}

int search(int U, int D)
{
    if (dep[U] > D)
        return 0LL;
    if (dep[U] == D)
        return 1LL;
    int targ1 = st[U], targ2 = en[U];
    int l = 0, r = (int)m1[D].size() - 1, lbound = -1, rbound = -1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (m1[D][m] >= targ1)
        {
            lbound = m;
            r = m - 1;
        }
        else
            l = m + 1;
    }
    if (lbound == -1)
        return 0LL;
    l = 0, r = (int)m1[D].size() - 1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (m1[D][m] <= targ2)
        {
            rbound = m;
            l = m + 1;
        }
        else
            r = m - 1;
    }
    if (rbound == -1)
        return 0LL;
    return rbound - lbound + 1;
}

void solve()
{
    cin >> n;
    for (int i = 2; i <= n; i++)
    {
        cin >> v;
        adj[v].PB(i);
        adj[i].PB(v);
    }
    dfs(1, 0);
    int q;
    cin >> q;
    while (q--)
    {
        cin >> u >> d;
        cout << search(u, d) << "\n";
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