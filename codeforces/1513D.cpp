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
const int MAX = 2e5 + 10;
vector<int> adj[MAX];

void solve()
{
    int n, p;
    cin >> n >> p;
    vector<pair<int, int>> arr(n);
    vector<int> a(n);
    vector<bool> is_connected(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].first;
        a[i] = arr[i].first;
        arr[i].second = i;
    }
    sort(all(arr));
    int i = 0;
    ll ans = 0;
    while (i < n)
    {
        int cur_val = arr[i].first;
        int cur_idx = arr[i].second;
        if (cur_val >= p)
            break;
        while (cur_idx > 0)
        {
            if (is_connected[cur_idx - 1])
                break;
            if (a[cur_idx - 1] % cur_val == 0)
            {
                is_connected[cur_idx - 1] = true;
                ans += cur_val;
                cur_idx--;
            }
            else
            {
                break;
            }
        }
        cur_idx = arr[i].second;
        while (cur_idx < n - 1)
        {
            if (is_connected[cur_idx])
                break;
            if (a[cur_idx + 1] % cur_val == 0)
            {
                is_connected[cur_idx] = true;
                ans += cur_val;
                cur_idx++;
            }
            else
            {
                break;
            }
        }
        i++;
    }
    for (int i = 0; i < n - 1; i++)
    {
        if (!is_connected[i])
            ans += p;
    }
    cout << ans << "\n";
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