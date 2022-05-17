#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
const ll MAX = 2e5 + 10;
ll factorial[MAX];

void precalc()
{
    for (int i = 0; i < MAX; i++)
    {
        if (i == 0)
            factorial[i] = 1;
        else
            factorial[i] = (factorial[i - 1] * i) % MOD;
    }
}

void solve()
{
    int n;
    cin >> n;
    vector<ll> arr(n);
    unordered_map<ll, ll> map1;
    map1.reserve(1024);
    map1.max_load_factor(0.25);
    ll and_sum = -1;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        if (and_sum == -1)
            and_sum = arr[i];
        else
            and_sum &= arr[i];
        map1[arr[i]] += 1;
    }
    if (map1[and_sum] < 2)
        cout << 0 << "\n";
    else
    {
        ll k = map1[and_sum];
        ll ans = (k * (k - 1)) % MOD;
        ans = (ans * factorial[n - 2]) % MOD;
        cout << ans << "\n";
    }
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