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

void solve()
{
    int n;
    cin >> n;
    ll ans = 0;
    ll prev = 0;
    for (int i = 0; i < n; i++)
    {
        ll tmp;
        cin >> tmp;
        if (i == 0)
            prev = tmp;
        ans += max(0LL, prev - tmp);
        prev = max(prev, tmp);
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}