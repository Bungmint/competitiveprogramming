#include <bits/stdc++.h>

using namespace std;
#define all(v) (v).begin(), (v).end()

int main()
{
    int k;
    string s;
    cin >> k >> s;
    int len = s.length();
    vector<int> prefix_sum(len + 1, 0);
    for (int i = 0; i < len; i++)
    {
        if (i == 0 && s[i] == '1')
            prefix_sum[i + 1] = 1;
        else
            prefix_sum[i + 1] = prefix_sum[i] + (s[i] == '1');
    }
    long long ans = 0;
    for (int i = 1; i <= len; i++)
    {
        int bef = prefix_sum[i - 1], target = k + bef;
        int l = i, r = len;
        int low, high = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (prefix_sum[mid] == target)
            {
                low = mid;
                r = mid - 1;
            }
            else if (prefix_sum[mid] > target)
            {
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        l = i, r = len;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (prefix_sum[mid] == target)
            {
                high = mid;
                l = mid + 1;
            }
            else if (prefix_sum[mid] > target)
            {
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        if (low == -1 || high == -1)
            continue;
        ans += (high - low + 1);
    }
    cout << ans << "\n";
    return 0;
}