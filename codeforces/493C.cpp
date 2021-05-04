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

void solve()
{
    int n;
    cin >> n;
    vector<int> fi(n);
    for (int i = 0; i < n; i++)
        cin >> fi[i];
    int m;
    cin >> m;
    vector<int> se(m);
    for (int i = 0; i < m; i++)
        cin >> se[i];
    sort(all(fi));
    sort(all(se));
    int ans = 3 * n - 3 * m;
    int a = 3 * n, b = 3 * m;
    int tar, j, sc, idx;
    for (int i = 0; i < n; i++)
    {
        tar = fi[i] - 1;
        j = lower_bound(all(fi), fi[i]) - fi.begin();
        sc = 3 * (n - j) + 2 * j;
        idx = upper_bound(all(se), tar) - se.begin();
        if (ans < sc - (idx)*2 - (m - idx) * 3)
        {
            a = sc;
            b = (idx)*2 + (m - idx) * 3;
            ans = sc - (idx)*2 - (m - idx) * 3;
        }
    }
    if (ans < 2 * n - 2 * m)
    {
        a = 2 * n;
        b = 2 * m;
    }
    cout << a << ":" << b << "\n";
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