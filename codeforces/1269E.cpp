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
int n;
vector<ll> BIT, BIT2;

void upd(int i)
{
    i++;
    for (int j = i; j <= n; j += (j & (-j)))
    {
        BIT[j]++;
    }
}
void upd(int i, int v)
{
    i++;
    for (int j = i; j <= n; j += (j & (-j)))
    {
        BIT2[j] += v;
    }
}

int query(int i)
{
    i++;
    int ans = 0;
    while (i > 0)
    {
        ans += BIT[i];
        i -= ((-i) & i);
    }
    return ans;
}

ll query2(int i)
{
    i++;
    ll ans = 0;
    while (i > 0)
    {
        ans += BIT2[i];
        i -= ((-i) & i);
    }
    return ans;
}

void solve()
{
    cin >> n;
    BIT.clear();
    BIT2.clear();
    BIT.resize(n + 1);
    BIT2.resize(n + 1);
    vector<ll> perm(n), pos(n + 1), off(n + 1), ans(n + 1), dp(n + 1);
    for (int i = 0; i < n; i++)
    {
        cin >> perm[i];
        pos[perm[i]] = i;
        upd(perm[i]);
        off[perm[i]] = perm[i] - 1 - query(perm[i] - 1);
    }
    for (int i = 1; i <= n; i++)
    {
        off[i] = off[i - 1] + off[i];
    }
    ordered_set<ll> lmfaoo;
    for (ll i = 1; i <= n; i++)
    {
        lmfaoo.insert(pos[i]);
        upd(pos[i], pos[i]);
        ll mid = *lmfaoo.find_by_order(i / 2);
        ll ls = query2(mid - 1);
        ll rs = query2(n - 1) - ls;
        ll lower = i / 2;
        ll upper = i - i / 2;
        dp[i] = (2 * mid - lower - 1) * (lower) / 2 - ls + rs - (2 * mid + upper - 1) * upper / 2;
    }

    ans[1] = 0;
    ll l = pos[1], r = pos[1];
    for (int i = 2; i <= n; i++)
    {
        r = max(pos[i], r);
        l = min(pos[i], l);
        ans[i] = off[i] + dp[i];
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
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