#pragma GCC optimize("O3")
#pragma GCC target("sse4")
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
    int n;
    cin >> n;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<pair<int, int>> time(n);
    for (int i = 0; i < n; i++)
    {
        cin >> time[i].first >> time[i].second;
    }
    sort(all(time));
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        while (!pq.empty() && pq.top().first < time[i].first)
        {
            pq.pop();
        }
        pq.push({time[i].second, time[i].first});
        ans = max(ans, (int)pq.size());
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