//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<ll> vec(n), pref(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }
    sort(all(vec));
    for (int i = 0; i < n; i++)
        pref[i] = (i == 0) ? vec[i] : vec[i] + pref[i - 1];
    ll ans = -LINF, num = -1;
    for (int i = 0; i < n; i++)
    {
        ll val = 0;
        ll l = i, r = n - 1;
        if (i == 0)
        {
            while (r >= l)
            {
                int m = l + (r - l) / 2;

                if (m == 0 || (m)*vec[m] - (pref[m - 1]) <= k)
                {
                    val = m + 1;
                    l = m + 1;
                }
                else
                    r = m - 1;
            }
        }
        else
        {
            while (r >= l)
            {
                ll m = l + (r - l) / 2;

                if (m == 0 || (m - i) * vec[m] - (pref[m - 1] - pref[i - 1]) <= k)
                {
                    val = m + 1 - i;
                    l = m + 1;
                }
                else
                    r = m - 1;
            }
        }
        if (ans < val)
        {
            num = vec[i + val - 1];
            ans = val;
        }
    }
    cout << ans << " " << num << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}