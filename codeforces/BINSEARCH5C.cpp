//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353

void solve()
{
    ll n, k;
    cin >> n >> k;
    k--;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    sort(all(a));
    sort(all(b));
    ll l = 1, r = 2e9 + 10, ans = -1;
    while (l <= r)
    {
        ll m = l + (r - l) / 2;
        ll targ = m - 1, sum = 0;
        for (int i = 0; i < n; i++)
        {
            if (a[i] >= targ)
                break;
            int l1 = 0, r1 = n - 1, val = -1;
            while (l1 <= r1)
            {
                int m1 = l1 + (r1 - l1) / 2;
                if (b[m1] <= targ - a[i])
                {
                    val = m1;
                    l1 = m1 + 1;
                }
                else
                    r1 = m1 - 1;
            }
            sum += val + 1;
        }
        if (sum <= k)
        {
            ans = m;
            l = m + 1;
        }
        else
            r = m - 1;
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}