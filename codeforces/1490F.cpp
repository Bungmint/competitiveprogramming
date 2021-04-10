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
        vector<ll> arr(n);
        unordered_map<ll, ll> map1;
        vector<ll> appearance;
        map1.reserve(1024);
        map1.max_load_factor(0.25);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
            map1[arr[i]] += 1;
        }
        for (auto x : map1)
        {
            appearance.push_back(x.second);
        }
        sort(appearance.begin(), appearance.end());
        int leng = appearance.size();
        int max_app = appearance[leng - 1];
        vector<int> prefix(leng);
        for (int i = 0; i < leng; i++)
        {
            if (i == 0)
                prefix[i] = appearance[i];
            else
                prefix[i] = prefix[i - 1] + appearance[i];
        }
        ll min_val = 1e9;
        for (int c = 0; c <= max_app; c++)
        {
            int l = 0, r = leng - 1, ans = -1;
            while (l <= r)
            {
                int mid = l + (r - l) / 2;
                if (appearance[mid] >= c)
                {
                    ans = mid;
                    r = mid - 1;
                }
                else
                {
                    l = mid + 1;
                }
            }
            if (ans == -1)
                continue;
            ll cost = (ans == 0) ? prefix[leng - 1] - c * leng : prefix[ans - 1] + (prefix[leng - 1] - prefix[ans - 1]) - c * (leng - ans);
            min_val = min(min_val, cost);
        }
        cout << min_val << "\n";
    }
}