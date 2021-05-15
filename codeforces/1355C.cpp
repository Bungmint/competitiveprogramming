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
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    ll ans = 0LL;
    for (int x = a; x <= b; x++)
    {
        ll minxy = max(c + 1, b + x), maxxy = c + x;
        ll turnt = d + 2;
        if (turnt <= maxxy && turnt >= minxy)
        {
            ans += (minxy + d - 2 * c + 1) * (d + 2 - minxy) / 2;
            ans += (d + 1 - c) * (maxxy - d - 1);
        }
        else if (minxy >= turnt)
        {
            ans += (d + 1 - c) * (maxxy - minxy + 1);
        }
        else
        {
            ans += (minxy + maxxy - 2 * c) * (maxxy - minxy + 1) / 2;
        }
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