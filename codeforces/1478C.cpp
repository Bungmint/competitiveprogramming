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
    ll n;
    cin >> n;
    vector<ll> d(2 * n);
    unordered_map<ll, int> m1;
    m1.reserve(1024);
    m1.max_load_factor(0.25);
    unordered_set<ll> s1;
    for (int i = 0; i < 2 * n; i++)
    {
        cin >> d[i];
        m1[d[i]]++;
    }
    for (auto x : m1)
    {
        if (x.second != 2)
        {
            cout << "NO"
                 << "\n";
            return;
        }
    }
    sort(all(d), [](ll x, ll y) {
        return x > y;
    });
    ll cumsum = 0LL, a;

    for (ll i = 0; i < n; i++)
    {
        if ((d[2 * i] - cumsum) % (2LL * (n - i)) != 0)
        {
            cout << "NO"
                 << "\n";
            return;
        }
        a = (d[2 * i] - cumsum) / (2LL * (n - i));
        if (s1.count(a) != 0 || a == 0)
        {
            cout << "NO"
                 << "\n";
            return;
        }
        s1.insert(a);
        cumsum += 2LL * a;
    }
    cout << "YES"
         << "\n";
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