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
const ll LINF = 1e15;
const int MOD = 1e9 + 7; //998244353

ll comb(ll a)
{
    if (a <= 1)
        return 0;
    return a * (a - 1) / 2;
}

void solve()
{
    int n;
    cin >> n;
    unordered_map<int, int, custom_hash> map1;
    for (int i = 0; i < n; i++)
    {
        int c;
        cin >> c;
        map1[c]++;
    }
    ll ans = 0LL;
    for (int i = 1; i <= n; i++)
    {
        if (map1.count(i) == 0)
            continue;
        ll cu = map1[i], plus1 = map1[i + 1], plus2 = map1[i + 2];
        ans += comb(cu) * (plus1 + plus2) + cu * (cu - 1) * (cu - 2) / 6 + comb(plus1) * cu + comb(plus2) * cu + plus1 * plus2 * cu;
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
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}