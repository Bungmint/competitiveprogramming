#include <bits/stdc++.h>

using namespace std;
using ll = long long;
ll dp[5001][5001];
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<ll> vec(n);
    vector<ll> intervals(n - m + 1);
    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }
    ll start = 0;
    for (int i = 0; i < m; i++)
    {
        start += vec[i];
    }
    intervals[0] = start;
    for (int i = 1; i < n - m + 1; i++)
    {
        intervals[i] = intervals[i - 1] + vec[i + m - 1] - vec[i - 1];
    }
    for (int i = 0; i < n - m + 1; i++)
    {
        dp[i + 1][1] = intervals[i];
    }
    for (int i = 1; i <= k; i++)
    {
        for (int j = 1; j <= n - m + 1; j++)
        {
            for (int l = j + m; l < n + 1 - m * (k - i - 2) && l <= n - m + 1; l++)
            {
                dp[l][i + 1] = max(dp[j][i] + intervals[l - 1], dp[l][i + 1]);
            }
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n - m + 1; i++)
    {
        ans = max(ans, dp[i][k]);
    }
    cout << ans << "\n";
    return 0;
}
