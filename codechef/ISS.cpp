//#pragma GCC optimize("Ofast")
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
const int N = 4e6 + 10;  // Only advised to use it under 1e7 (More Memory)
int lp[N + 1];
vector<int> pr;

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
}

const int POG = 1e6 + 10;

ll preproc[POG];

void pre()
{
    for (int i = 1; i <= 1e6; i++)
    {
        ll pogga = 1LL;
        ll num = 4 * i + 1;
        while (num > 1)
        {
            ll prime = lp[num];
            ll cnt = 0;
            while (num % prime == 0)
            {
                cnt++;
                num /= prime;
            }
            pogga *= (cnt + 1) * mod_pow(prime, cnt) - cnt * mod_pow(prime, cnt - 1);
        }
        pogga = pogga - (pogga - 4 * i - 1) / 2 - 1;
        preproc[i] = pogga;
    }
}

void solve()
{
    ll k;
    cin >> k;
    cout << preproc[k] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    linsieve();
    pre();
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