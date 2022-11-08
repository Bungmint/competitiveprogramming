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

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<ll, int>>> path(n, vector<pair<ll, int>>(m));
    vector<int> ans(m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> path[i][j].first;
            path[i][j].second = j;
        }
    }
    for (int i = 0; i < n; i++)
    {
        sort(all(path[i]));
    }
    vector<pair<ll, int>> track(m);
    for (int i = 0; i < m; i++)
    {
        track[i].second = i;
        track[i].first = path[0][i].first;
        ans[track[i].second] = path[0][i].first;
    }
    for (auto x : ans)
        cout << x << " ";
    cout << "\n";
    for (int i = 1; i < n; i++)
    {
        sort(all(track));
        for (int j = 0; j < m; j++)
        {
            ans[track[j].second] = path[i][m - j - 1].first;
            track[j].first = min(track[j].first, path[i][m - j - 1].first);
        }
        for (auto x : ans)
            cout << x << " ";
        cout << "\n";
    }
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