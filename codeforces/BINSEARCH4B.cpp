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
const int N = 1e5 + 10;
vector<pair<int, int>> adj[N];
int arr[N], p[N], n, m;
double dist[N], temp[N];
vector<int> ans;

bool bfs(double targ)
{
    memset(p, -1, sizeof(p));
    for (int i = 1; i <= n; i++)
        dist[i] = LINF;
    queue<int> q;
    dist[1] = 0LL;
    q.push(1);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (auto e : adj[v])
        {
            if (dist[e.first] > dist[v] + (double)arr[e.second] - targ)
            {
                dist[e.first] = dist[v] + arr[e.second] - targ;
                p[e.first] = v;
                q.push({e.first});
            }
        }
    }
    return (dist[n] <= (double)0);
}

void solve()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        arr[i] = w;
        adj[u].PB({v, i});
    }
    double l = 0, r = 200;
    while (r - l > 1e-7)
    {
        double mid = (l + r) / 2;
        if (bfs(mid))
        {
            ans.clear();
            for (int i = n; i >= 1; i = p[i])
                ans.PB(i);
            r = mid;
        }
        else
        {
            l = mid;
        }
    }
    cout << ans.size() - 1 << "\n";
    reverse(all(ans));
    for (auto x : ans)
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