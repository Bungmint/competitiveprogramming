#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int dp[1 << 17][17];

int cost(const vector<int> &vec1, const vector<int> &vec2)
{
    return abs(vec1[0] - vec2[0]) + abs(vec1[1] - vec2[1]) + max(0, vec2[2] - vec1[2]);
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> coords(n, vector<int>(3));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> coords[i][j];
        }
    }
    memset(dp, -1, sizeof(dp));
    dp[1][0] = 0;
    for (int i = 1; i < (1 << n); i += 2)
    {
        ll unvisited = ((1 << n) - 1) ^ i;
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                if (dp[i][j] == -1)
                    continue;
                for (int k = 0; k < n; k++)
                {
                    if (unvisited & (1 << k))
                    {
                        if (dp[i | (1 << k)][k] == -1)
                        {
                            dp[i | (1 << k)][k] = dp[i][j] + cost(coords[j], coords[k]);
                        }
                        dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], dp[i][j] + cost(coords[j], coords[k]));
                    }
                }
            }
        }
    }
    int ans = 1e9;
    for (int i = 1; i < n; i++)
    {
        if (dp[(1 << n) - 1][i] == -1)
        {
            cout << "ERROR" << endl;
            continue;
        }
        ans = min(ans, cost(coords[i], coords[0]) + dp[((1 << n) - 1)][i]);
    }
    cout << ans << "\n";
}