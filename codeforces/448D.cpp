#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll f(ll x, int n, int m)
{
    ll res = 0;
    x--;
    for (int i = 1; i <= n; i++)
    {
        res += min((ll)m, x / i);
    }
    return res;
}

int main()
{
    ll n, m, k;
    cin >> n >> m >> k;
    ll l = 1, r = n * m + 1;
    while (l < r)
    {
        ll mid = l + (r - l) / 2;
        if (f(mid, n, m) < k)
            l = mid + 1;
        else
            r = mid;
    }
    cout << l - 1 << "\n";
}