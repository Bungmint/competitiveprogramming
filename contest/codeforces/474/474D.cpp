#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll MAX = 1e5 + 10;
const ll MOD = 1e9 + 7;
ll dp[MAX][2];
ll prefix[MAX];
int k;

void solve()
{
    dp[0][0] = 1;
    dp[0][1] = 0;

    for (int i = 1; i < 1e5 + 7; i++)
    {
        dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) % MOD;
        if (i >= k)
            dp[i][1] = (dp[i - k][0] + dp[i - k][1]) % MOD;
    }
    for (int i = 0; i < MAX; i++)
    {
        if (i == 0)
            prefix[i] = (dp[i + 1][0] + dp[i + 1][1]) % MOD;
        else
            prefix[i] = (prefix[i - 1] + dp[i + 1][0] + dp[i + 1][1]) % MOD;
    }
}

int main()
{
    int t;
    cin >> t >> k;
    solve();
    while (t--)
    {
        int a, b;
        cin >> a >> b;
        (a == 1) ? cout << prefix[b - 1] << "\n" : cout << (prefix[b - 1] - prefix[a - 2] + MOD) % MOD << "\n";
    }
}