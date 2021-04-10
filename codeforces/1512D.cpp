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
    int n;
    cin >> n;
    vector<ll> b(n + 2);
    ll sum = 0;
    for (int i = 0; i < n + 2; i++)
    {
        cin >> b[i];
        sum += b[i];
    }
    sort(all(b));
    vector<ll> ans;
    bool found = false;
    int idx = 0;
    for (int i = 0; i < n + 2; i++)
    {
        ll exclude = b[i];
        if (i == n + 1 && b[n] == sum - b[i] - b[n] && !found)
        {
            for (int j = 0; j < n; j++)
            {
                ans.push_back(b[j]);
            }
            found = true;
        }
        if ((i != n + 1) && b[n + 1] == sum - b[i] - b[n + 1] && !found)
        {
            for (int j = 0; j < i; j++)
            {
                ans.push_back(b[j]);
            }
            for (int j = i + 1; j <= n; j++)
            {
                ans.push_back(b[j]);
            }
            found = true;
        }
    }
    if (ans.size() == 0)
        cout << -1 << "\n";
    else
    {
        for (int i = 0; i < n; i++)
        {
            cout << ans[i] << " ";
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