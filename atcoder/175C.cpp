#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
    ll x, k, d;
    cin >> x >> k >> d;
    x = llabs(x);
    ll quotient = x / d;
    if (k <= quotient)
    {
        cout << llabs(x - k * d) << "\n";
    }
    else
    {
        if (k % 2 == quotient % 2)
        {
            cout << llabs(x - quotient * d) << "\n";
        }
        else
        {
            cout << llabs(x - (quotient + 1) * d) << "\n";
        }
    }
    return 0;
}