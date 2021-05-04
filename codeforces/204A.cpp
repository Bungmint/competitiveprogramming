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
ll dp[18], pref[18];

ll pow(ll base, ll exp)
{
    if (exp == 0)
        return 1;
    if (exp == 1)
        return base;
    ll m = pow(base, exp / 2);
    if (exp % 2 == 0)
        return m * m;
    else
        return m * m * base;
}

ll under(ll x)
{
    if (x < 10)
        return x;
    ll sz = 0, res = 0;
    while (pow(10LL, sz) < x)
        sz++;
    if (pow(10LL, sz) == x)
    {
        return pref[sz - 1];
    }
    ll quo = x / pow(10LL, sz - 1LL);
    res += pref[sz - 2] + (quo - 1LL) * pow(10LL, sz - 2LL);
    ll num = x - quo * pow(10LL, sz - 1LL) - (x % 10);
    num /= 10;
    if (x % 10 < quo)
    {
        res += num;
    }
    else
    {
        res += num + 1;
    }
    return res;
}

void solve()
{
    ll l, r;
    cin >> l >> r;
    for (int i = 0; i < 18; i++)
    {
        if (i == 0 || i == 1)
            dp[i] = 9LL;
        else
        {
            dp[i] = 9LL;
            for (int j = 0; j < i - 1; j++)
            {
                dp[i] *= 10LL;
            }
        }
        if (i == 0)
            pref[i] = dp[i];
        else
            pref[i] = pref[i - 1] + dp[i];
    }
    cout << under(r) - under(l - 1) << "\n";
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