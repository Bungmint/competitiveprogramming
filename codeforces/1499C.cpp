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
    ll n;
    cin >> n;
    vector<ll> c(n);
    ll ans = LINF;
    ll esum = 0LL, osum = 0LL, eval = 0LL, oval = 0LL, emin = LINF, omin = LINF;
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            if (c[i] < emin)
            {
                eval = c[i] * (n - i / 2) + esum;
                emin = c[i];
            }
            else
            {
                eval += c[i] - emin;
            }
        }
        else
        {
            if (c[i] < omin)
            {
                oval = c[i] * (n - (i - 1) / 2) + osum;
                omin = c[i];
            }
            else
            {
                oval += c[i] - omin;
            }
        }
        if (i != 0)
            ans = min(ans, oval + eval);
        if (i % 2 == 0)
            esum += c[i];
        else
            osum += c[i];
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t-- > 0)
    {
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}