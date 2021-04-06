#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> beacons(n);
    for (int i = 0; i < n; i++)
    {
        cin >> beacons[i].first >> beacons[i].second;
    }
    sort(all(beacons));
    vector<int> dp(n, 0);
    int res = dp[0] + n - 1;
    for (int i = 1; i < n; i++)
    {
        int cur_pos = beacons[i].first, target_val = cur_pos - beacons[i].second - 1;
        int l = 0, r = i, ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (target_val >= beacons[mid].first)
            {
                ans = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        if (ans == -1)
        {
            dp[i] = i;
        }
        else
        {
            dp[i] = dp[ans] + i - ans - 1;
        }
        res = min(res, dp[i] + (n - 1 - i));
    }
    cout << res << "\n";
    return 0;
}