#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, t;
    cin >> n >> t;
    vector<int> sum_vec(n);
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        if (i == 0)
            sum_vec[i] = tmp;
        else
            sum_vec[i] = sum_vec[i - 1] + tmp;
    }
    int ans = 0, target_val;

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
            target_val = t;
        else
            target_val = t + sum_vec[i - 1];
        int idx = -1;
        int L = i, R = n - 1;
        while (L <= R)
        {
            int mid = L + (R - L) / 2;
            if (sum_vec[mid] <= target_val)
            {
                idx = mid;
                L = mid + 1;
            }
            else
            {
                R = mid - 1;
            }
        }
        if (idx == -1)
            continue;
        ans = max(ans, idx - i + 1);
    }
    cout << ans << "\n";
    return 0;
}