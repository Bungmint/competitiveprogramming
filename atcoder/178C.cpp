#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

ll pow(ll a, ll b, ll m)
{
    ll ans = 1;
    while (b)
    {
        if (b & 1)
            ans = (ans * a) % m;
        b /= 2;
        a = (a * a) % m;
    }
    return ans;
}

int main()
{
    int n;
    cin >> n;
    ll ans = (pow(10ll, n, MOD) - pow(9ll, n, MOD) - pow(9ll, n, MOD) + pow(8ll, n, MOD) + 2 * MOD) % MOD;
    cout << ans << "\n";
    return 0;
}