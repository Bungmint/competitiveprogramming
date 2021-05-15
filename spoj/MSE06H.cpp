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
const int N = 1010;
int BIT[N];

void upd(int i)
{
    for (i++; i < N; i += (-i) & i)
        BIT[i]++;
}
int query(int i)
{
    int ans = 0;
    for (i++; i > 0; i -= (-i) & i)
        ans += BIT[i];
    return ans;
}

void solve()
{
    memset(BIT, 0, sizeof(BIT));
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> road(k);
    vector<vector<int>> vec(n);
    for (int i = 0; i < k; i++)
    {
        cin >> road[i].first >> road[i].second;
        vec[road[i].first - 1].PB(road[i].second - 1);
    }
    ll ans = 0LL;
    for (int i = 0; i < n; i++)
    {
        for (auto x : vec[i])
        {
            ans += query(m) - query(x);
        }
        for (auto x : vec[i])
        {
            upd(x);
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        cout << "Test case " << i << ": ";
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}