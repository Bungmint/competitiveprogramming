#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
const int MAX = 1e5 + 10;
vector<pair<int, int>> adj[MAX];
ll dist[MAX];
int parent[MAX];
int n, m;

void dijkstra(int V)
{
    memset(parent, -1, sizeof(parent));
    for (int i = 1; i <= n; i++)
    {
        dist[i] = LINF;
    }
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
    q.push({0, V});
    while (!q.empty())
    {
        ll d = q.top().first;
        int v = q.top().second;
        q.pop();
        if (dist[v] < d)
            continue;
        for (auto x : adj[v])
        {
            int e = x.first;
            ll w = x.second;
            if (dist[e] > d + w)
            {
                dist[e] = d + w;
                parent[e] = v;
                q.push({dist[e], e});
            }
        }
    }
}

void solve()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }
    dijkstra(1);
    parent[1] = -1;
    vector<int> ans;
    int j = n;
    while (parent[j] != -1)
    {
        ans.push_back(parent[j]);
        j = parent[j];
    }
    if (dist[n] == LINF)
        cout << -1 << "\n";
    else
    {
        reverse(all(ans));
        for (auto x : ans)
            cout << x << " ";
        cout << n << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}