#include <bits/stdc++.h>

using namespace std;
const int MAX = 105;
const int INF = 1e9;
int dp[MAX][4];
int act[MAX];

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> act[i];
    }
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            dp[i][j] = INF;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            dp[0][0] = 1;
            if (act[0] == 1)
                dp[0][1] = 0;
            else if (act[0] == 2)
                dp[0][2] = 0;
            else if (act[0] == 3)
            {
                dp[0][1] = 0;
                dp[0][2] = 0;
            }
        }
        else
        {
            dp[i][0] = 1 + min({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]});
            if (act[i] == 1)
            {
                dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]);
            }
            else if (act[i] == 2)
            {
                dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]);
            }
            else if (act[i] == 3)
            {
                dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]);
                dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]);
            }
        }
    }
    cout << min(min(dp[n - 1][0], dp[n - 1][1]), dp[n - 1][2]) << "\n";
    return 0;
}