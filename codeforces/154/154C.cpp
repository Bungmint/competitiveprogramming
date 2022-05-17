#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll MOD = pow(2, 64);
ll p53[2000000];

void precalc()
{
    for (int i = 0; i < 1999000; i++)
    {
        if (!i)
            p53[i] = 1;
        else
            p53[i] = (p53[i - 1] * 31) % MOD;
    }
}

ll mod_pow(ll base, ll exp)
{
    if (!exp)
        return 0;
    if (exp == 1)
        return 1;
    ll mid = mod_pow(base, exp / 2);
    if (exp % 2 == 0)
        return (mid * mid) % MOD;
    else
        return (((mid * mid) % MOD) * mid) % MOD;
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    precalc();
    int n, m;
    cin >> n >> m;
    vector<ll> hashtable(n + 1, 0);
    vector<unordered_set<int>> friends(n + 1);
    unordered_map<ll, ll> hash_maps(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        hashtable[a] = (hashtable[a] + p53[b - 1]) % MOD;
        hashtable[b] = (hashtable[b] + p53[a - 1]) % MOD;
        friends[a].insert(b);
        friends[b].insert(a);
    }
    for (int i = 1; i <= n; i++)
    {
        hash_maps[hashtable[i]] += 1;
        hashtable[i] = (hashtable[i] + p53[i - 1]) % MOD;
    }
    for (int i = 1; i <= n; i++)
    {
        hash_maps[hashtable[i]] += 1;
    }
    ll ans = 0;
    for (auto const &x : hash_maps)
    {
        ans += x.second * (x.second - 1) / 2;
    }
    cout << ans << "\n";
    return 0;
}