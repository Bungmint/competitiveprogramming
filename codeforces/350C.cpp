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
    vector<pair<int, int>> bombs(n);
    ll ans = 0;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        ans += 2 + (x != 0) * 2 + (y != 0) * 2;
        bombs[i].first = x;
        bombs[i].second = y;
    }
    sort(all(bombs), [](pair<int, int> p1, pair<int, int> p2) {
        return llabs(p1.first) + llabs(p1.second) < llabs(p2.second) + llabs(p2.first);
    });
    cout << ans << "\n";
    for (int i = 0; i < n; i++)
    {
        int x = bombs[i].first, y = bombs[i].second;
        if (x > 0)
            cout << 1 << " " << x << " R"
                 << "\n";
        else if (x == 0)
        {
        }
        else
            cout << 1 << " " << -x << " L\n";
        if (y > 0)
            cout << 1 << " " << y << " U"
                 << "\n";
        else if (y == 0)
        {
        }
        else
            cout << 1 << " " << -y << " D"
                 << "\n";
        cout << 2 << "\n";
        if (x > 0)
            cout << 1 << " " << x << " L"
                 << "\n";
        else if (x == 0)
        {
        }
        else
            cout << 1 << " " << -x << " R\n";
        if (y > 0)
            cout << 1 << " " << y << " D"
                 << "\n";
        else if (y == 0)
        {
        }
        else
            cout << 1 << " " << -y << " U"
                 << "\n";
        cout << 3 << "\n";
    }
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