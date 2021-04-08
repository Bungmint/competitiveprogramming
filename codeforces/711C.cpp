#include <bits/stdc++.h>

using namespace std;
using ll = long long;
ll dp[105][105][105];
ll liter[105][105];
int c[105];

int main()
{
    int n, m, k;
    memset(dp, -1, sizeof(dp));
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> liter[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            if (c[i] != 0)
                dp[i][c[i]][1] = 0;
            else
            {
                for (int j = 1; j <= m; j++)
                {
                    dp[i][j][1] = liter[i][j];
                }
            }
            continue;
        }
        if (c[i] != 0)
        {
            for (int j = 1; j <= k; j++)
            {
                for (int l = 1; l <= m; l++)
                {
                    if (dp[i - 1][l][j] != -1)
                    {
                        if (dp[i][c[i]][j + (c[i] != l)] != -1)
                        {
                            dp[i][c[i]][j + (c[i] != l)] = min(dp[i][c[i]][j + (c[i] != l)], dp[i - 1][l][j]);
                        }
                        else
                        {
                            dp[i][c[i]][j + (c[i] != l)] = dp[i - 1][l][j];
                        }
                    }
                }
            }
        }
        else
        {
            for (int j = 1; j <= k; j++)
            {
                for (int col1 = 1; col1 <= m; col1++)
                {
                    for (int colb = 1; colb <= m; colb++)
                    {
                        if (dp[i - 1][colb][j] != -1)
                        {
                            if (dp[i][col1][j + (col1 != colb)] != -1)
                            {
                                dp[i][col1][j + (col1 != colb)] = min(dp[i][col1][j + (col1 != colb)], dp[i - 1][colb][j] + liter[i][col1]);
                            }
                            else
                            {
                                dp[i][col1][j + (col1 != colb)] = dp[i - 1][colb][j] + liter[i][col1];
                            }
                        }
                    }
                }
            }
        }
    }
    ll ans = 1e13;
    for (int i = 1; i <= m; i++)
    {
        if (dp[n - 1][i][k] != -1)
        {
            ans = min(ans, dp[n - 1][i][k]);
        }
    }
    if (ans == 1e13)
        cout << -1 << "\n";
    else
        cout << ans << "\n";
}