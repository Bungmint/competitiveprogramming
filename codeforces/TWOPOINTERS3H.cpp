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
    ll n, m, s, A, B;
    cin >> n >> m >> s >> A >> B;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
        cin >> b[i];
    sort(all(a), [](int x, int y) {
        return x > y;
    });
    sort(all(b), [](int x, int y) {
        return x > y;
    });
    int l = 0;
    ll res = 0LL, weight = 0LL, cost = 0LL;
    for (int r = 0; r < n; r++)
    {
        weight += A;
        cost += a[r];
        while (l < m && weight + B <= s)
        {
            weight += B;
            cost += b[l];
            l++;
        }
        while (l > 0 && weight > s)
        {
            l--;
            weight -= B;
            cost -= b[l];
        }
        if (weight <= s)
            res = max(res, cost);
    }
    weight = 0, cost = 0;
    l = 0;
    for (int r = 0; r < m; r++)
    {
        weight += B;
        cost += b[r];
        while (l < n && weight + A <= s)
        {
            weight += A;
            cost += a[l];
            l++;
        }
        while (l > 0 && weight > s)
        {
            l--;
            weight -= A;
            cost -= a[l];
        }
        if (weight <= s)
            res = max(res, cost);
    }
    cout << res << "\n";
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