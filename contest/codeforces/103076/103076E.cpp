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
ll dp[200010], local[100010];

struct Frac
{
    ll x, y;
};

int quad(Frac f1)
{
    if (f1.x >= 0)
    {
        if (f1.y >= 0)
        {
            return 1;
        }
        return 4;
    }
    if (f1.y >= 0)
    {
        return 2;
    }
    return 3;
}

bool cmp(pair<Frac, ll> p1, pair<Frac, ll> p2)
{
    int q1 = quad(p1.first), q2 = quad(p2.first);
    if (q1 != q2)
        return q1 < q2;
    return p1.first.y * p2.first.x < p1.first.x * p2.first.y;
}

void solve()
{
    int n;
    cin >> n;
    vector<pair<Frac, ll>> planets(n);

    for (int i = 0; i < n; i++)
    {
        int x, y, a, s, g;
        cin >> x >> y >> a >> s;
        g = abs(gcd(x, y));
        planets[i].first = {x / g, y / g};
        planets[i].second = a - s;
    }
    Frac prev = {0, 0};
    int cnt = -1;
    sort(all(planets), cmp);
    for (int i = 0; i < n; i++)
    {
        if (prev.x != planets[i].first.x || prev.y != planets[i].first.y)
        {
            prev = planets[i].first;
            cnt++;
            dp[cnt] += planets[i].second;
        }
        else
        {
            dp[cnt] += planets[i].second;
        }
    }
    cnt++;
    for (int i = cnt; i < 2 * cnt; i++)
    {
        dp[i] = dp[i - cnt];
    }
    for (int i = 1; i < 2 * cnt; i++)
    {
        dp[i] += dp[i - 1];
    }
    ll cur = LINF;
    for (int i = cnt - 1; i >= 0; i--)
    {
        cur = min(cur, dp[i]);
        local[i] = cur;
    }
    ll mini = 0LL, ans = 0;
    for (int i = 0; i < cnt; i++)
    {
        ans = max(ans, dp[i] - mini);
        mini = min(mini, dp[i]);
    }
    for (int i = cnt; i < 2 * cnt; i++)
    {
        ans = max(ans, dp[i] - local[i - cnt]);
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}