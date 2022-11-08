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
vector<pair<int, bool>> adj[N];
int dist[N], n, m;

void pogbfs()
{
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    deque<int> deq;
    dist[1] = 0;
    deq.push_front(1);
    while (!deq.empty())
    {
        int v = deq.front();
        deq.pop_front();
        for (auto x : adj[v])
        {
            if (x.second && dist[x.first] > dist[v])
            {
                dist[x.first] = dist[v];
                deq.push_back(x.first);
            }
            if (!x.second && dist[x.first] > dist[v] + 1)
            {
                dist[x.first] = dist[v] + 1;
                deq.push_back(x.first);
            }
        }
    }
}

void solve()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].PB({v, true});
        adj[v].PB({u, false});
    }
    pogbfs();
    if (dist[n] == INF)
        cout << -1 << "\n";
    else
        cout << dist[n] << "\n";
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