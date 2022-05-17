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
const int Ps = 6e4 + 10;
const int N = 1e5 + 10;
vector<vector<int>> adj;
ll n, primes[Ps], m, subtree[N], edges[N];

void dfdp(ll V, ll pV)
{
    ll sub = 1LL;
    for (auto e : adj[V])
    {
        if (e != pV)
        {
            dfdp(e, V);
            sub += subtree[e];
            edges[e] = subtree[e] * (n - subtree[e]);
        }
    }
    subtree[V] = sub;
}

void solve()
{
    memset(primes, 0, sizeof(primes));
    memset(edges, 0, sizeof(edges));
    memset(subtree, 0, sizeof(subtree));
    cin >> n;
    adj.clear();
    adj.resize(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].PB(v);
        adj[v].PB(u);
    }
    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> primes[i];
    sort(primes, primes + m, [](ll x, ll y) {
        return x > y;
    });
    if (m > n - 1)
    {
        for (int i = 1; i < m - n + 2; i++)
        {
            primes[i] = primes[i] * primes[i - 1] % MOD;
        }
    }
    dfdp(1, 0);
    sort(edges + 2, edges + n + 1, [](ll x, ll y) {
        return x > y;
    });
    ll ans = 0LL;
    if (m > n - 1)
    {
        for (int i = m - n + 1; i < m; i++)
        {
            ans = (ans + edges[i - m + n + 1] * primes[i]) % MOD;
        }
    }
    else
    {
        for (int i = 2; i <= n; i++)
        {
            if (i <= m + 1)
                ans = (ans + (((edges[i]) % MOD * primes[i - 2]) % MOD) % MOD) % MOD;
            else
                ans = (ans + edges[i]) % MOD;
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}