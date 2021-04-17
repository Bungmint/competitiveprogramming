#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;
ll adj[MAX];
bool vis[MAX];

int dfs(int x, int start, bool is_start)
{
    if (x == start && !is_start)
        return 0;
    vis[x] = true;
    return 1 + dfs(adj[x], start, false);
}

ll loop_pair(ll k)
{
    return k * k;
}

void solve()
{
    memset(vis, false, sizeof(vis));
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> adj[i];
    }
    vector<ll> loop;
    for (int i = 1; i <= n; i++)
    {
        if (vis[i])
            continue;
        ll lo = dfs(i, i, true);
        loop.push_back(lo);
    }
    if (loop.size() == 1)
        cout << loop_pair(loop[0]) << "\n";
    else
    {
        sort(all(loop), [](ll x, ll y) {
            return x > y;
        });
        ll ans = 0;
        ans += loop_pair(loop[0] + loop[1]);
        for (int i = 2; i < loop.size(); i++)
        {
            ans += loop_pair(loop[i]);
        }
        cout << ans << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}