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
vector<pair<int, int>> adj[100001];
int vis[100001];
int p[100001], dist[100001];
int n, m, d;

bool bfs(int t)
{
    memset(vis, false, sizeof(vis));
    queue<int> q;
    q.push(1);
    vis[1] = true;
    p[1] = -1;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        if (dist[v] == d)
            continue;
        for (auto e : adj[v])
        {
            if (vis[e.second])
                continue;
            if (e.first > t)
                continue;
            vis[e.second] = true;
            q.push(e.second);
            dist[e.second] = dist[v] + 1;
            p[e.second] = v;
        }
    }
    return vis[n];
}

void solve()
{
    cin >> n >> m >> d;
    while (m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].PB({w, v});
    }
    int l = 0, r = 1e9, ans = INT_MAX;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (bfs(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    if (!bfs(ans))
    {
        cout << -1 << "\n";
        return;
    }
    vector<int> res;
    int v = n;
    while (v != -1)
    {
        res.PB(v);
        v = p[v];
    }
    cout << (int)res.size() - 1 << "\n";
    reverse(all(res));
    for (auto x : res)
        cout << x << " ";
    cout << "\n";
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