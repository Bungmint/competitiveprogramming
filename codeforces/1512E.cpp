#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;

void solve()
{
    int n, l, r, s;
    cin >> n >> l >> r >> s;
    int k = r - l + 1;
    if ((2 * n - k + 1) * k / 2 < s || s < k * (k + 1) / 2)
        cout << -1 << "\n";
    else
    {
        unordered_set<int> set1;
        set1.reserve(1024);
        set1.max_load_factor(0.25);
        vector<int> vec(n);
        int cur_sum = 0;
        for (int i = l - 1; i <= r - 1; i++)
        {
            vec[i] = n - (i - l + 1);
            cur_sum += vec[i];
        }

        int idx = r - 1;
        while (cur_sum > s && idx >= l - 1)
        {
            int reduce = vec[idx];
            if (idx == r - 1)
            {
                reduce -= min(cur_sum - s, reduce - 1);
                cur_sum -= vec[idx] - reduce;
                vec[idx] = reduce;

                set1.insert(vec[idx]);
                idx--;
            }
            else
            {
                reduce -= min(cur_sum - s, reduce - 1 - vec[idx + 1]);
                cur_sum -= vec[idx] - reduce;
                vec[idx] = reduce;
                set1.insert(vec[idx]);
                idx--;
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (vec[i] == 0)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (set1.count(j) == 0)
                    {
                        vec[i] = j;
                        set1.insert(j);
                        break;
                    }
                }
            }
        }
        for (auto x : vec)
        {
            cout << x << " ";
        }
        cout << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}