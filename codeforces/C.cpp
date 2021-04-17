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
ll dp[2001][2001];

void solve()
{
    int n;
    cin >> n;
    vector<ll> speed(n);
    for (int i = 0; i < n; i++)
    {
        cin >> speed[i];
    }
    sort(all(speed));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = LINF;
        }
    }
    for (int i = 0; i < n; i++)
    {
        dp[i][i] = 0;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i; j < n; j++)
        {
            if (j < n - 1)
                dp[i][j + 1] = min(dp[i][j] + speed[j + 1] - speed[i], dp[i][j + 1]);
            if (i > 0)
                dp[i - 1][j] = min(dp[i][j] + speed[j] - speed[i - 1], dp[i - 1][j]);
        }
    }
    ll ans = dp[0][n - 1];

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