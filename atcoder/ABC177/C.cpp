#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

int main()
{
    int n;
    cin >> n;
    ll ans = 0;
    ll sum = 0;
    vector<ll> A(n);
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
        sum += A[i];
        sum %= MOD;
    }
    for (int i = 0; i < n; i++)
    {
        ans += A[i] * (sum - A[i] + MOD);
        sum -= A[i];
        sum = (sum + MOD) % MOD;
        ans %= MOD;
    }
    cout << ans << "\n";
    return 0;
}