#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll MOD = 998244353;
const int MAX = 2e5 + 7;
ll dp[MAX];

int main()
{
    ll n, k;
    cin >> n >> k;
    vector<pair<ll, ll>> segments(k);
    for (int i = 0; i < k; i++)
    {
        cin >> segments[i].first >> segments[i].second;
    }
    dp[1] = 1;
    for (ll i = 2; i <= n; i++)
    {
        ll cur = 0;
        for (int j = 0; j < k; j++)
        {
            if (segments[j].first >= i)
                continue;
            int l = max(1LL, i - segments[j].second);
            int r = i - segments[j].first;
            cur += dp[r] - dp[l - 1];
            cur %= MOD;
        }
        if (cur < 0)
            cur += MOD;
        dp[i] = dp[i - 1] + cur;
        dp[i] %= MOD;
    }
    cout << (dp[n] - dp[n - 1] + MOD) % MOD << "\n";
}