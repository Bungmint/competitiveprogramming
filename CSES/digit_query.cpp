//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
vector<ll> digits(18);

ll pow(ll base, ll exp)
{
    if (exp == 0)
        return 1;
    if (exp == 1)
        return base;
    ll mid = pow(base, exp / 2);
    if (exp % 2 == 0)
        return mid * mid;
    else
        return mid * mid * base;
}

void precalc()
{
    for (ll i = 1; i <= 18; i++)
    {
        if (i == 1)
            digits[i] = 9;
        else
            digits[i] = digits[i - 1] + i * 9 * pow(10LL, i - 1);
    }
}

void solve()
{
    ll k;
    cin >> k;
    auto idx = lower_bound(all(digits), k) - digits.begin();
    ll len = idx;
    ll div = (k - digits[idx - 1] + len - 1) / len;
    ll remainder = (k - digits[idx - 1]) % len;
    ll ans = pow(10LL, len - 1) - 1 + div;
    string s = to_string(ans);
    if (remainder == 0)
        remainder = len;
    cout << s[remainder - 1] << "\n";
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
}