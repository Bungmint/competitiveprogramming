#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int MAX = 1e5 + 10;
ll dp[MAX][2];
string normal[MAX];
string reversed[MAX];
ll c[MAX];

int main()
{
    int n;
    string tmp, tmp2;
    cin >> n;
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> tmp;
        tmp2 = tmp;
        normal[i] = tmp;
        reverse(tmp2.begin(), tmp2.end());
        reversed[i] = tmp2;
    }

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            dp[i][0] = 0;
            dp[i][1] = c[i];
            continue;
        }
        if (normal[i] >= normal[i - 1] && (dp[i - 1][0] != -1))
        {
            dp[i][0] = dp[i - 1][0];
        }
        if (normal[i] >= reversed[i - 1] && (dp[i - 1][1] != -1))
        {
            if (dp[i][0] != -1)
                dp[i][0] = min(dp[i][0], dp[i - 1][1]);
            else
                dp[i][0] = dp[i - 1][1];
        }
        if (reversed[i] >= normal[i - 1] && (dp[i - 1][0] != -1))
        {
            dp[i][1] = dp[i - 1][0] + c[i];
        }
        if (reversed[i] >= reversed[i - 1] && (dp[i - 1][1] != -1))
        {
            if (dp[i][1] != -1)
                dp[i][1] = min(dp[i][1], dp[i - 1][1] + c[i]);
            else
                dp[i][1] = dp[i - 1][1] + c[i];
        }
    }
    if (dp[n - 1][0] != -1 && dp[n - 1][1] != -1)
    {
        cout << min(dp[n - 1][0], dp[n - 1][1]) << "\n";
    }
    else if (dp[n - 1][0] != -1)
    {
        cout << dp[n - 1][0] << "\n";
    }
    else if (dp[n - 1][1] != -1)
    {
        cout << dp[n - 1][1] << "\n";
    }
    else
    {
        cout << -1 << "\n";
    }
}