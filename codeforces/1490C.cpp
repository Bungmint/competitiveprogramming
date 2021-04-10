#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll MAX = 1e4 + 10;
unordered_set<ll> cubed;

void precalc()
{
    for (int i = 1; i < MAX; i++)
    {
        cubed.insert(pow(i, 3));
    }
}

int main()
{
    int t;
    cin >> t;
    cubed.reserve(1024);
    cubed.max_load_factor(0.25);
    precalc();
    while (t--)
    {
        ll x;
        cin >> x;
        bool ok = false;
        for (int i = 1; i < MAX; i++)
        {
            if (pow(i, 3) > x)
                break;
            ll num = x - pow(i, 3);
            if (cubed.count(num) == 1)
                ok = true;
        }
        if (ok)
            cout << "YES"
                 << "\n";
        else
            cout << "NO"
                 << "\n";
    }
}