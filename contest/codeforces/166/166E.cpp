#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int MAX = 1e7 + 7, MOD = 1e9 + 7;
int dp[MAX][4];

int main()
{
    int n;
    cin >> n;
    dp[1][0] = 1, dp[1][1] = 1, dp[1][2] = 1, dp[1][3] = 0;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j <= 3; j++)
        {
            dp[i][j] = ((dp[i][j] + dp[i - 1][(j + 1) % 4]) % MOD + (dp[i - 1][(j + 2) % 4] + dp[i - 1][(j + 3) % 4]) % MOD) % MOD;
        }
    }
    cout << dp[n][3] % MOD << "\n";
    return 0;
}
