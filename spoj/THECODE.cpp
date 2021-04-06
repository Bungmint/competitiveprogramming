#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        int n, d;
        cin >> n >> d;
        string num;
        vector<int> dp(1 << 10, 4095);
        dp[0] = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> num;
            int mask = 0;
            for (int j = 0; j <= d - 1; j++)
            {
                mask |= 1 << (num[j] - '0');
            }
            for (int j = 0; j < (1 << 10); j++)
            {
                dp[j | mask] = min(dp[j | mask], dp[j] + 1);
            }
        }
        (dp[1023] == 4095) ? cout << -1 << endl : cout << dp[1023] << endl;
    }
    return 0;
}