//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
const int MAX = 2007;
vector<int> adj[MAX];
int dp[MAX][MAX];
int dist[MAX];
int parent[MAX];
unordered_map<pair<int, int>, vector<int>> forb;
int n, m, k;

void dijkstra(int V)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, V});
    for (int i = 1; i <= n; i++)
        dist[i] = (i == V) ? 0 : INF;
    while (!q.empty())
    {
        int v = q.top().second;
        int d = q.top().first;
        if (d > dist[v])
            continue;
        for (auto x : adj[v])
        {
            if (dist[x] > d + 1 &&)
            {
            }
        }
    }
}

void solve()
{

    cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[b].PB(a);
        adj[a].PB(b);
    }
    forb.reserve(1024);
    forb.max_load_factor(0.25);
    for (int i = 0; i < k; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        forb[make_pair(a, b)].PB(c);
    }

    if (parent[n] == 0)
        cout << -1 << "\n";
    else
    {
        vector<int> ans;
        int j = n;
        ans.PB(j);
        while (parent[j] != -1)
        {
            ans.PB(parent[j]);
            j = parent[j];
        }
        reverse(all(ans));
        cout << ans.size() - 1 << "\n";
        for (auto x : ans)
            cout << x << " ";
        cout << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}