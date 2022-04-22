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
vector<ll> t, y, z, loop;
ll n, m;

bool good(ll time)
{
    ll b = 0;
    for (int i = 0; i < n; i++)
    {
        b += time / loop[i] * z[i] + min(z[i], (time % loop[i]) / t[i]);
    }
    return b >= m;
}

void solve()
{
    cin >> m >> n;
    t.resize(n);
    y.resize(n);
    z.resize(n);
    loop.resize(n);
    for (int i = 0; i < n; i++)
        cin >> t[i] >> z[i] >> y[i];
    for (int i = 0; i < n; i++)
        loop[i] = t[i] * z[i] + y[i];
    ll l = -1;  // BAD
    ll r = 1e9; // GOOD
    while (l + 1 < r)
    {
        ll mid = (l + r) / 2;
        if (good(mid))
        {
            r = mid;
        }
        else
            l = mid;
    }
    cout << r << "\n";
    ll total = 0;
    for (ll i = 0; i < n; i++)
    {
        total += r / loop[i] * z[i] + min(z[i], (r % loop[i]) / t[i]);
    }
    for (ll i = 0; i < n; i++)
    {
        ll bs = r / loop[i] * z[i] + min(z[i], (r % loop[i]) / t[i]);
        if (total > m)
        {
            ll tmp = min(bs, total - m);
            bs -= tmp;
            total -= tmp;
        }
        cout << bs << " ";
    }
    cout << "\n";
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