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
using ld = long double;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7; //998244353
const int MAX = 1e5 + 10;
vector<pair<int, ld>> adj[MAX];
pair<pair<int, int>, ld> edge[MAX];
ld sub[MAX], n, q;
ld N = 0LL;

ld comb(ld a)
{
    if (a <= 1)
        return 0LL;
    return (a - 1) * a / 2LL;
}

void subtree(int V, int pV)
{
    sub[V] = 1;
    for (auto &e : adj[V])
    {
        if (e.first != pV)
        {
            subtree(e.first, V);
            sub[V] += sub[e.first];
        }
    }
}

void dfs(int V, int pV)
{
    for (auto &e : adj[V])
    {
        if (e.first == pV)
            continue;
        dfs(e.first, V);
        ld num = sub[e.first];
        N += 2 * e.second * (comb(num) * (n - num) + comb(n - num) * num);
    }
}

void solve()
{
    cin >> n;
    ld total = n * (n - 1) * (n - 2) / 6;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v, l;
        cin >> u >> v >> l;
        edge[i + 1] = {{u, v}, l};
        adj[u].PB({v, l});
        adj[v].PB({u, l});
    }
    subtree(1, 0);
    dfs(1, 0);
    cin >> q;
    cout << setprecision(20);
    while (q--)
    {
        int r, w;
        cin >> r >> w;
        int u = edge[r].first.first, v = edge[r].first.second;
        if (sub[u] < sub[v])
            swap(u, v);
        N += 2 * (w - edge[r].second) * (comb(sub[v]) * (n - sub[v]) + comb(n - sub[v]) * sub[v]);
        edge[r].second = w;
        cout << (ld)N / (ld)total << "\n";
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