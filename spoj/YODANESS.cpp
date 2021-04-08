#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<string> yoda(n);
        vector<int> BIT(n + 1);
        unordered_map<string, int> order;
        order.reserve(1024);
        order.max_load_factor(0.25);
        vector<string> normal(n);
        for (int i = 0; i < n; i++)
        {
            cin >> yoda[i];
        }
        for (int i = 0; i < n; i++)
        {
            cin >> normal[i];
            order[normal[i]] = i;
        }
        long long ans = 0;
        for (int i = 0; i < n; i++)
        {
            long long cur_idx = order[yoda[i]] + 1, end_idx = n, num_below = 0, num_above = 0;
            for (int j = cur_idx; j <= n; j += j & (-j))
            {
                BIT[j] += 1;
            }
            while (cur_idx)
            {
                num_below += BIT[cur_idx];
                cur_idx -= cur_idx & (-cur_idx);
            }
            while (end_idx)
            {
                num_above += BIT[end_idx];
                end_idx -= end_idx & (-end_idx);
            }
            ans += num_above - num_below;
        }
        cout << ans << "\n";
    }
    return 0;
}