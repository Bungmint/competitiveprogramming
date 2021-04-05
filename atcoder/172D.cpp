#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll MAX = 1e7 + 1;
ll arr[MAX];

void precalc()
{
    for (ll i = 1; i < MAX; i++)
    {
        for (ll j = 1; j <= MAX / i; j++)
        {
            arr[i * j] += 1;
        }
    }
}

int main()
{
    precalc();
    ll n;
    cin >> n;
    ll total = 0;
    for (ll i = 1; i <= n; i++)
    {
        total += arr[i] * i;
    }
    cout << total << "\n";
    return 0;
}