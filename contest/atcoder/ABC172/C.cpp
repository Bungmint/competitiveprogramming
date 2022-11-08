#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define pb push_back

int main()
{
    ll n, m, k, tmp;
    cin >> n >> m >> k;
    vector<ll> A, a = {0};
    vector<ll> B, b = {0};
    for (ll i = 0; i < n; i++)
    {
        cin >> tmp;
        A.pb(tmp);
    }
    for (ll i = 0; i < m; i++)
    {
        cin >> tmp;
        B.pb(tmp);
    }
    for (ll i = 0; i < n; i++)
    {
        a.pb(a[i] + A[i]);
    }
    for (ll i = 0; i < m; i++)
    {
        b.pb(b[i] + B[i]);
    }
    ll ans = 0, j = m;
    for (ll i = 0; i <= n; i++)
    {
        if (a[i] > k)
            break;
        while (b[j] > k - a[i])
        {
            j--;
        }
        ans = max(ans, i + j);
    }
    cout << ans << "\n";
    return 0;
}