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

ll mod_pow(ll base, ll exp)
{
    if (exp == 0)
        return 1;
    if (exp == 1)
        return base;
    ll mid = mod_pow(base, exp / 2);
    if (exp % 2 == 0)
        return (mid * mid) % MOD;
    else
        return (((mid * mid) % MOD) * base) % MOD;
}

void solve()
{
    ll n;
    cin >> n;
    cout << mod_pow(2, n) << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}