#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
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
        vector<int> BIT(n + 1);
        vector<int> data(n);
        vector<int> not_sorted(n);
        vector<int> BIT_wit_no_swag(n + 1);
        for (int i = 0; i < n; i++)
        {
            cin >> data[i];
            not_sorted[i] = data[i];
        }
        sort(all(data));
        long long ans = 0;
        for (int i = 0; i < n; i++)
        {
            long long idx = lower_bound(all(data), not_sorted[i]) - data.begin();
            for (int j = idx + 1; j <= n; j += j & (-j))
            {
                BIT_wit_no_swag[j] += 1;
            }
            long long cur_val = 0, cur_val2 = 0, idx2 = n;
            idx = upper_bound(all(data), not_sorted[i]) - data.begin();
            while (idx)
            {
                cur_val += BIT_wit_no_swag[idx];
                idx -= idx & (-idx);
            }
            while (idx2)
            {
                cur_val2 += BIT_wit_no_swag[idx2];
                idx2 -= idx2 & (-idx2);
            }
            ans += cur_val2 - cur_val;
        }
        cout << ans << "\n";
    }
    return 0;
}
