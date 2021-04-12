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
const int MAX = 2e5 + 10;
ll arr[MAX];

void precalc()
{
    unordered_map<int, ll> digits;
    digits.reserve(1024);
    digits.max_load_factor(0.25);
    digits[0] = 1;
    for (int i = 0; i < MAX; i++)
    {
        ll zero = digits[0];
        ll one = digits[1];
        ll two = digits[2];
        ll three = digits[3];
        ll four = digits[4];
        ll five = digits[5];
        ll six = digits[6];
        ll seven = digits[7];
        ll eight = digits[8];
        ll nine = digits[9];
        digits[1] = (zero + nine) % MOD;
        digits[2] = one % MOD;
        digits[3] = two % MOD;
        digits[4] = three % MOD;
        digits[5] = four % MOD;
        digits[6] = five % MOD;
        digits[7] = six % MOD;
        digits[8] = seven % MOD;
        digits[9] = eight % MOD;
        digits[0] = nine % MOD;
        for (int j = 0; j < 10; j++)
        {
            arr[i] += digits[j];
        }
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;

    unordered_map<int, ll> digits;
    digits.reserve(1024);
    digits.max_load_factor(0.25);
    while (n > 0)
    {
        int last = n % 10;
        digits[last] += 1;
        n /= 10;
    }
    ll ans = 0;
    for (int i = 0; i < 10; i++)
    {
        ans += digits[i] * arr[m + i - 1];
        ans %= MOD;
    }
    cout << ans << "\n";
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