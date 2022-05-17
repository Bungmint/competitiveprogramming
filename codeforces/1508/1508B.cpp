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

void recur(ll sz, ll start, ll K)
{
    if (sz <= 0)
        return;
    if (sz == 1)
    {
        cout << start << " ";
        return;
    }
    ll pos = 1LL, cnt = 0;
    while (pos < K && cnt < sz - 1)
    {
        pos *= 2LL;
        cnt++;
    }
    assert(pos >= K);
    if (cnt == sz - 1)
    {
        pos /= 2;
        K -= pos;
        ll st = -1;
        for (int i = start + 1; i < start + sz; i++)
        {
            st = i;
            pos /= 2;
            if (K <= pos)
                break;
            K -= pos;
        }
        for (int i = st; i >= start; i--)
            cout << i << " ";
        recur(sz - (st - start + 1), st + 1, K);
    }
    else
    {
        cout << start << " ";
        recur(sz - 1, start + 1, K);
    }
}

void solve()
{
    ll n, k;
    cin >> n >> k;
    ll pos = 1LL, cnt = 0;
    while (pos < k && cnt < n - 1)
    {
        pos *= 2;
        cnt++;
    }
    if (pos < k)
    {
        cout << -1 << "\n";
        return;
    }
    recur(n, 1LL, k);
    cout << "\n";
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