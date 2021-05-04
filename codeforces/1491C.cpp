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
    int n;
    cin >> n;
    vector<int> tramp(n);
    vector<int> pekora(n);
    ll ans = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> tramp[i];
    }
    for (int i = 0; i < n; i++)
    {
        ans += max(tramp[i] - 1 - pekora[i], 0);
        for (int j = 2; j <= tramp[i]; j++)
        {
            if (j + i > n - 1)
                break;
            pekora[i + j]++;
        }
        if (i < n - 1)
            pekora[i + 1] += max(0, pekora[i] - tramp[i] + 1);
    }
    cout << ans << "\n";
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