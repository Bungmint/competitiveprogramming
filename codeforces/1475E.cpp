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
const int N = 1010;
ll fact[N];

void precalc()
{
    for (ll i = 0; i < N; i++)
    {
        if (i == 0)
            fact[i] = 1LL;
        else
            fact[i] = (i * fact[i - 1]) % MOD;
    }
}

ll mod_pow(ll base, ll exp)
{
    if (exp == 0)
        return 1LL;
    if (exp == 1)
        return base;
    ll m = mod_pow(base, exp / 2);
    if (exp % 2 == 0)
        return (m * m) % MOD;
    return (((m * m) % MOD) * base) % MOD;
}

ll inv_mod(ll a)
{
    return mod_pow(a, MOD - 2);
}

ll nCk(ll n, ll k)
{
    if (n < k)
        return 0LL;
    return (((fact[n] * inv_mod(fact[k])) % MOD) * inv_mod(fact[n - k])) % MOD;
}

void solve()
{
    int k, n;
    cin >> n >> k;
    vector<int> nums(n + 1);
    for (int i = 0; i < n; i++)
    {
        int fol;
        cin >> fol;
        nums[fol]++;
    }
    int dec = -1;
    for (int i = n; i >= 1; i--)
    {
        if (k == 0)
            break;
        if (nums[i] > k)
        {
            dec = i;
            break;
        }
        k -= nums[i];
    }
    if (dec == -1)
    {
        cout << 1LL << "\n";
        return;
    }
    cout << nCk(nums[dec], k) << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    precalc();
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