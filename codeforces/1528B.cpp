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
const int MOD = 998244353;
const int N = 1e6 + 1;
ll pref[N], f[N];
int lp[2 * N + 1], numdiv[2 * N + 1];
vector<int> pr;
void linsieve()
{
    for (int i = 2; i <= 2 * N; i++)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= 2 * N; ++j)
        {
            lp[i * pr[j]] = pr[j];
        }
    }
}

void calc()
{
    numdiv[1] = 1;
    for (int i = 2; i < 2 * N; i++)
    {
        if (lp[i] == i)
        {
            numdiv[i] = 2;
        }
        else
        {
            int prime = lp[i];
            int nu = i, cnt = 0;
            while (nu % prime == 0)
            {
                cnt++;
                nu /= prime;
            }
            numdiv[i] = numdiv[nu] * (cnt + 1);
        }
    }

    for (int i = 1; i < N; i++)
    {
        if (i == 1)
        {
            pref[i] = 1;
            f[i] = 1;
            continue;
        }
        else
        {
            f[i] = (pref[i - 1] + numdiv[i]) % MOD;
            pref[i] = (pref[i - 1] + f[i]) % MOD;
        }
    }
}

void solve()
{
    int n;
    cin >> n;
    cout << f[n] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    linsieve();
    calc();
    solve();
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}