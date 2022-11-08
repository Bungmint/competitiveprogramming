//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;

void solve()
{
    int n, x;
    cin >> n >> x;
    vector<int> vec(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }
    int ans = n, prev = -1;
    sort(all(vec));
    for (int i = 0; i < n; i++)
    {
        if (vec[i] > x)
            break;
        if (i == 0)
            prev = n;
        int target = x - vec[i];
        int l = i + 1, r = prev - 1, res = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (vec[mid] <= target)
            {
                res = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        if (res != -1)
        {
            ans--;
            prev = res;
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}