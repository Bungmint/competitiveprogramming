#include <bits/stdc++.h>

using namespace std;
using ll = long long;
ll dp[(1LL << 18) + 10][20];
vector<unordered_map<int, ll>> adj(23);

int main()
{
    memset(dp, -1, sizeof(dp));
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<ll> food(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> food[i];
    }
    for (int i = 0; i <= k - 1; i++)
    {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        adj[a][b] = c;
    }
    for (int i = 0; i <= n - 1; i++)
    {
        dp[1LL << i][i + 1] = food[i + 1];
    }
    ll max_satisfaction = -1;
    for (int i = 1; i < (1LL << n); i++)
    {
        for (int l = 1; l <= n; l++)
        {
            ll not_eaten = ((1LL << n) - 1) ^ i;
            ll cur_sat = dp[i][l];
            if (cur_sat == -1)
                continue;
            if (__builtin_popcount(i) == m)
            {
                max_satisfaction = max(cur_sat, max_satisfaction);
                continue;
            }
            int before = l;
            for (int j = 0; j <= n - 1; j++)
            {
                if (not_eaten & (1 << (j)))
                {
                    if (adj[before].count(j + 1) > 0)
                    {
                        ll pos = dp[i][l] + food[j + 1] + adj[before][j + 1];
                        if (pos > dp[i | 1 << j][j + 1])
                        {
                            dp[i | (1 << j)][j + 1] = dp[i][l] + food[j + 1] + adj[before][j + 1];
                        }
                    }
                    else
                    {
                        ll pos = dp[i][l] + food[j + 1];
                        if (pos > dp[i | 1 << j][j + 1])
                        {
                            dp[i | (1 << j)][j + 1] = dp[i][l] + food[j + 1];
                        }
                    }
                }
            }
        }
    }
    cout << max_satisfaction << "\n";
    return 0;
}