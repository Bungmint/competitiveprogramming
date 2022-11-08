#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<ll> prefix(n);
        vector<ll> prefix_sum_sum(n, 1);
        vector<pair<ll, ll>> vec(n);
        vector<ll> idx;
        for (int i = 0; i < n; i++)
        {
            cin >> vec[i].first;
            vec[i].second = i;
        }
        sort(vec.begin(), vec.end());
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
                prefix[i] = vec[i].first;
            else
                prefix[i] = prefix[i - 1] + vec[i].first;
        }

        for (int i = 0; i < n - 1; i++)
        {
            if (prefix[i] >= vec[i + 1].first)
                prefix_sum_sum[i + 1] += prefix_sum_sum[i];
        }
        cout << prefix_sum_sum[n - 1] << "\n";
        for (int i = 0; i < prefix_sum_sum[n - 1]; i++)
        {
            idx.push_back(vec[n - i - 1].second);
        }
        sort(idx.begin(), idx.end());
        for (auto x : idx)
        {
            cout << x + 1 << " ";
        }
        cout << "\n";
    }
}