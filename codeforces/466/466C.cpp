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
vector<ll> BIT;
int n;

void update(ll idx, ll val)
{
    idx++;
    for (int j = idx; j <= n; j += (j & -j))
    {
        BIT[j] += val;
    }
}

ll query(ll idx)
{
    idx++;
    ll ans = 0LL;
    for (int j = idx; j >= 1; j -= (j & -j))
    {
        ans += BIT[j];
    }
    return ans;
}

void solve()
{
    cin >> n;
    BIT.resize(n + 1);
    vector<ll> pref(n);
    ll sum = 0LL;
    for (int i = 0; i < n; i++)
    {
        ll tmp;
        cin >> tmp;
        if (i == 0)
            pref[i] = tmp;
        else
            pref[i] = pref[i - 1] + tmp;
        sum += tmp;
    }
    if (sum % 3 != 0)
    {
        cout << 0 << "\n";
        return;
    }
    ll targ1 = sum / 3, targ2 = sum * 2 / 3;
    ll ans = 0LL;
    for (ll i = 0; i < n - 1; i++)
    {
        if (pref[i] == targ1)
        {
            update(i, 1LL);
        }
        if (pref[i] == targ2)
        {
            ans += query(i - 1);
        }
    }
    cout << ans << "\n";
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