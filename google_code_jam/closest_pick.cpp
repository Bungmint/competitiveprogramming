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

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> p(n), vals(n + 1);
    for (int i = 0; i < n; i++)
        cin >> p[i];
    sort(all(p));
    int d, maximal = 0LL;
    for (int i = 0; i <= n; i++)
    {
        if (i == 0)
            d = p[0] - 1;
        else if (i == n)
            d = k - p[n - 1];
        else
            d = p[i] - p[i - 1];
        maximal = max(maximal, d - 1);
        if (i != 0 && i != n)
            vals[i] = d / 2;
        else
            vals[i] = d;
    }
    sort(all(vals));
    maximal = max(maximal, vals[n] + vals[n - 1]);
    cout << setprecision(10) << (long double)maximal / (long double)k << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        cout << "CASE #" << i << ": ";
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}