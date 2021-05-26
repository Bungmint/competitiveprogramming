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

void upd(int i, int v)
{
    i++;
    for (int j = i; j <= n; j += j & (-j))
        BIT[j] += v;
}
void update(int l, int r, int v)
{
    upd(l, v);
    upd(r + 1, -v);
}
ll query(int i)
{
    i++;
    ll ans = 0LL;
    while (i > 0)
    {
        ans += BIT[i];
        i -= i & (-i);
    }
    return ans;
}

void solve()
{
    cin >> n;
    BIT.resize(n + 1);
    vector<ll> a(n), b(n), diff(n), target(n);
    set<pair<ll, int>> apos;
    ll as = 0, bs = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        as += a[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
        bs += b[i];
        apos.insert({b[i] + i, i});
    }
    if (as != bs)
    {
        cout << -1 << "\n";
    }
    for (int i = 0; i < n; i++)
    {
        ll targ = a[i] + i;
        pair<ll, int> p1 = *apos.lower_bound({targ, -INF});
        if (p1.first != targ)
        {
            cout << -1 << "\n";
            return;
        }
        apos.erase(p1);
        update(i, i, p1.second - i);
        target[p1.second] = i;
    }
    ll ans = 0LL;
    for (int i = 0; i < n; i++)
    {
        int cur = target[i];
        int mov = query(cur);
        ans += abs(mov);
        if (mov > 0)
        {
            update(cur, i, 1);
        }
        else if (mov < 0)
            update(i, cur, -1);
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