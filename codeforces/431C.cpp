#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
ll arr_low[201] = {0};
ll arr_normal[201] = {0};

ll solve(ll n, ll k, ll d)
{
    arr_low[100] = 1;
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j < d; j++)
        {
            if (i < j)
                break;
            arr_low[i + 100] += arr_low[i + 100 - j];
            arr_low[i + 100] %= mod;
        }
    }
    arr_normal[100] = 1;
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= k; j++)
        {
            if (i < j)
                break;
            arr_normal[i + 100] += arr_normal[i + 100 - j];
            arr_normal[i + 100] %= mod;
        }
    }
    ll res = arr_normal[100 + n] - arr_low[100 + n];
    if (res < 0)
    {
        return res + mod;
    }
    return res % mod;
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ll n, k, d;
    cin >> n >> k >> d;
    if (d > n)
    {
        cout << 0 << "\n";
    }
    else
    {
        cout << solve(n, k, d) << "\n";
    }
    return 0;
}