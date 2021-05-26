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
vector<ar<ll, 3>> adj[N];
map<int, ll> s1[N];
pair<ll, ll> dist[N][2];
ll n, m, C, q, s;

void dijkstra()
{
    ll u, d, cprev;
    priority_queue<ar<ll, 3>, vector<ar<ll, 3>>, greater<ar<ll, 3>>> pq;
    dist[s][0] = {C + 1, 0};
    dist[s][1] = {C + 1, 0};
    pq.push({dist[s][0].second, C + 1, s}); //dis, prevcol, node
    while (!pq.empty())
    {
        u = pq.top()[2], d = pq.top()[0], cprev = pq.top()[1];
        pq.pop();
        if (s1[u].count(cprev))
            continue;
        s1[u][cprev] = d;
        for (auto e : adj[u])
        {
            if (e[1] == cprev)
                continue;
            int col1 = dist[e[0]][0].first, col2 = dist[e[0]][1].first;
            if (col1 == e[1])
            {
                if (dist[e[0]][0].second > d + e[2])
                {
                    dist[e[0]][0].second = d + e[2];
                    pq.push({dist[e[0]][0].second, col1, e[0]});
                }
            }
            else if (col2 == e[1])
            {
                if (dist[e[0]][1].second > d + e[2])
                {
                    dist[e[0]][1].second = d + e[2];
                    pq.push({dist[e[0]][1].second, col2, e[0]});
                }
            }
            else
            {
                if (col1 == 0)
                {
                    dist[e[0]][0] = {e[1], d + e[2]};
                    pq.push({dist[e[0]][0].second, e[1], e[0]});
                }
                else if (col2 == 0)
                {
                    dist[e[0]][1] = {e[1], d + e[2]};
                    pq.push({dist[e[0]][1].second, e[1], e[0]});
                }
                else
                {
                    if (dist[e[0]][0].second > d + e[2] && dist[e[0]][1].second > d + e[2])
                    {
                        if (dist[e[0]][0].second > dist[e[0]][1].second)
                        {
                            dist[e[0]][0] = {e[1], d + e[2]};
                            pq.push({dist[e[0]][0].second, e[1], e[0]});
                        }
                        else
                        {
                            dist[e[0]][1] = {e[1], d + e[2]};
                            pq.push({dist[e[0]][1].second, e[1], e[0]});
                        }
                    }
                    else if (dist[e[0]][0].second > d + e[2])
                    {
                        dist[e[0]][0] = {e[1], d + e[2]};
                        pq.push({dist[e[0]][0].second, e[1], e[0]});
                    }
                    else if (dist[e[0]][1].second > d + e[2])
                    {
                        dist[e[0]][1] = {e[1], d + e[2]};
                        pq.push({dist[e[0]][1].second, e[1], e[0]});
                    }
                }
            }
        }
    }
}

void solve()
{
    cin >> n >> m >> C;
    for (int i = 0; i < m; i++)
    {
        ll u, v, c, w;
        cin >> u >> v >> w >> c;
        adj[u].PB({v, c, w});
    }
    cin >> s >> q;
    dijkstra();
    while (q--)
    {
        int t;
        cin >> t;
        if (dist[t][0].first == 0 && dist[t][1].first == 0)
            cout << -1 << "\n";
        else
        {
            if (dist[t][0].first == 0)
                cout << dist[t][1].second << "\n";
            else if (dist[t][1].first == 0)
                cout << dist[t][0].second << "\n";
            else
                cout << min(dist[t][0].second, dist[t][1].second) << "\n";
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