#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;
ll arr[2007];

void precalc(int num)
{
    arr[0] = 1;
    for (int i = 3; i <= num; i++)
    {
        arr[i] = (arr[i - 1] + arr[i - 3]) % MOD;
    }
}

ll pow(ll a, ll b, ll m)
{
    if (a == 0)
        return 1;
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
    int s;
    cin >> s;
    precalc(2005);
    ll ans = arr[s];
    cout << ans << "\n";
    return 0;
}