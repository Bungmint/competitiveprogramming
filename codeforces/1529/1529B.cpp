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
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    sort(all(v));
    int zr = 0, pos = 0, neg = 0;
    int neggap = INT32_MAX, small = INT32_MAX;
    for (int i = 0; i < n; i++)
    {
        if (v[i] > 0)
        {
            pos++;
            small = min(small, v[i]);
        }
        if (v[i] < 0)
        {
            neg++;
            if (i > 0)
                neggap = min(neggap, abs(v[i] - v[i - 1]));
        }
        if (v[i] == 0)
        {
            zr++;
            if (i > 0 || v[i - 1] < 0)
                neggap = min(neggap, abs(v[i - 1]));
        }
    }
    if (neg == 0)
    {
        cout << max(zr, min(zr, 1) + min(pos, 1)) << "\n";
        return;
    }
    if (pos == 0)
    {
        cout << neg + zr << "\n";
        return;
    }
    if (zr == 0)
    {
        if (small <= neggap)
            cout << neg + 1 << "\n";
        else
            cout << neg << "\n";
        return;
    }
    if (zr >= 2)
    {
        cout << zr + neg << "\n";
        return;
    }
    if (zr == 1)
    {
        if (neggap >= small)
            cout << neg + 2 << "\n";
        else
            cout << neg + 1 << "\n";
    }
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