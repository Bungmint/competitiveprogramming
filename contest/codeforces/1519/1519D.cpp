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
ll dp[5001][5001];
int n;
vector<ll> a, b;

ll dping(int i, int j)
{
    if (dp[i][j] != -LINF)
        return dp[i][j];
    if (j == 2)
    {
        dp[i][j] = (a[i] - a[i + 1]) * (b[i + 1] - b[i]);
        return dp[i][j];
    }
    if (j == 3)
    {
        dp[i][j] = (a[i] - a[i + 2]) * (b[i + 2] - b[i]);
        return dp[i][j];
    }
    dp[i][j] = dping(i + 1, j - 2) + (a[i] - a[i + j - 1]) * (b[i + j - 1] - b[i]);
    return dp[i][j];
}

void solve()
{
    for (int i = 0; i <= 5000; i++)
    {
        for (int j = 0; j <= 5000; j++)
        {
            dp[i][j] = -LINF;
        }
    }
    cin >> n;
    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    ll ans = 0LL;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            ans = max(ans, dping(i, j - i + 1));
        }
    }
    for (int i = 0; i < n; i++)
    {
        ans += a[i] * b[i];
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