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
const int N = 2e7 + 10;  // Only advised to use it under 1e7 (More Memory)
int lp[N + 1], pre[N];
vector<int> pr;
void linsieve()
{
    for (int i = 2; i <= N; i++)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
        {
            lp[i * pr[j]] = pr[j];
        }
    }
    for (int i = 2; i < N; i++)
    {
        pre[i] = pre[i / lp[i]] + (lp[i / lp[i]] != lp[i]);
    }
}

int gcd(int a, int b, int &x, int &y)
{
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1)
    {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

ll pospair(int num)
{
    ll ans = 1LL;
    while (num > 1)
    {
        int prim = lp[num];
        while (num % prim == 0)
        {
            num /= prim;
        }
        ans *= 2LL;
    }
    return ans;
}

ll mod_pow(ll base, ll exp)
{
    if (exp == 0)
        return 1LL;
    if (exp == 1)
        return base;
    ll m = mod_pow(base, exp / 2);
    if (exp % 2 == 0)
        return (m * m);
    return (((m * m)) * base);
}

void solve()
{
    int c, d, x;
    cin >> c >> d >> x;
    ll ans = 0;
    for (int i = 1; i * i <= x; i++)
    {
        if (x % i != 0)
            continue;
        int k1 = i + d, k2 = x / i + d;
        if (k1 % c == 0)
            ans += mod_pow(2, pre[k1 / c]);
        if (k2 % c == 0 && k1 != k2)
            ans += mod_pow(2, pre[k2 / c]);
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    linsieve();
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