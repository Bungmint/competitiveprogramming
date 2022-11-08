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
#define bigInt __int128_t
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 998244353;
const int LOG = 20;
int n, m;
vector<int> cities[50001];

ll mod_pow(ll a, ll b)
{
    if (b == 1)
        return a;
    ll m1 = mod_pow(a, b / 2);
    if (b % 2 == 0)
        return (m1 * m1) % MOD;
    return (((m1 * m1) % MOD) * a) % MOD;
}

__int128_t read()
{
    __int128_t x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(__int128_t x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
bool cmp(__int128_t x, __int128_t y) { return x > y; }

__int128_t gcd1(__int128_t x, __int128_t y)
{
    while (y)
    {
        __int128_t c = y;
        y = x % c;
        x = c;
    }
    return x;
}

void solve()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int d;
            cin >> d;
            cities[j].PB(d);
        }
    }
    ll denom = 1;
    for (int i = 1; i <= n; i++)
        denom *= i;
    for (int i = 0; i < m; i++)
        sort(all(cities[i]));
    __int128_t num = 0LL;
    for (int i = 0; i < m; i++)
    {
        __int128_t val = 1LL;
        for (int j = 0; j < n; j++)
        {
            val *= (cities[i][j] - j - 1);
        }
        num += (denom - val);
    }
    bigInt g = gcd1(num, denom);
    num /= g, denom /= g;
    num %= MOD;
    denom %= MOD;
    ll a = num, b = denom;
    cout << (a * mod_pow(b, MOD - 2)) % MOD << "\n";
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