//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
bool vis[100001], is_tree = true;
vector<int> adj[100001];

void dfs(int V, int parent)
{
    if (vis[V])
        return;
    vis[V] = true;
    for (auto v1 : adj[V])
    {
        if (v1 != parent)
        {
            if (vis[v1])
                is_tree = false;
            dfs(v1, V);
        }
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].PB(y);
        adj[y].PB(x);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (vis[i])
            continue;
        is_tree = true;
        dfs(i, 0);
        if (is_tree)
            ans++;
    }
    cout << ans << "\n";
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