#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;

void solve()
{
    int n;
    cin >> n;
    vector<ll> w(n);
    for (int i = 0; i < n; i++)
    {
        cin >> w[i];
    }
    ll ans = LINF;
    for (ll i = 1; i < (1LL << n); i++)
    {
        ll j = (1LL << n) - 1 - i;
        ll part1 = 0;
        ll part2 = 0;
        for (int m = 0; m < n; m++)
        {
            if (i & (1 << m))
                part1 += w[m];
        }
        for (int m = 0; m < n; m++)
        {
            if (j & (1 << m))
                part2 += w[m];
        }
        ans = min(ans, abs(part1 - part2));
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}