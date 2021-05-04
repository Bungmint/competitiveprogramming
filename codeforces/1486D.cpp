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
    int n, k, l, r = 0, ans = -1;
    cin >> n >> k;
    vector<int> vec(n), pref(n), mod(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
        r = max(r, vec[i]);
    }
    l = 1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        for (int i = 0; i < n; i++)
        {
            if (vec[i] >= m)
            {
                mod[i] = 1;
            }
            else
            {
                mod[i] = -1;
            }
            if (i == 0)
                pref[i] = mod[i];
            else
                pref[i] = pref[i - 1] + mod[i];
        }
        int minimum = 0, mx = pref[k - 1];
        for (int i = k; i < n; i++)
        {
            minimum = min(minimum, pref[i - k]);
            mx = max(mx, pref[i] - minimum);
        }
        if (mx > 0)
        {
            ans = m;
            l = m + 1;
        }
        else
        {
            r = m - 1;
        }
    }
    cout << ans << "\n";
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