#pragma GCC optimize("O3")
#pragma GCC target("sse4")
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
    int n, k;
    cin >> n >> k;
    if (n == 1)
        if (k == 1)
            cout << -1 << "\n";
        else
            cout << 1 << "\n";
    else
    {
        if (n < 2 * k + 1)
            cout << -1 << "\n";
        else
        {
            vector<int> ans(n, -1);
            unordered_set<int> used;
            used.reserve(1024);
            used.max_load_factor(0.25);
            for (int i = 0; i < k; i++)
            {
                ans[i * 2 + 1] = n - i;
                used.insert(n - i);
            }
            for (int i = 0; i < n; i++)
            {
                if (ans[i] == -1)
                {
                    for (int j = 1; j <= n; j++)
                    {
                        if (used.count(j) == 0)
                        {
                            ans[i] = j;
                            used.insert(j);
                            break;
                        }
                    }
                }
            }
            for (auto x : ans)
                cout << x << " ";
            cout << "\n";
        }
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
