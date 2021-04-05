#include <bits/stdc++.h>

using namespace std;
using ll = long long;
ll pow(ll a, ll b, ll m)
{
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

int phi(int n)
{
    int result = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

int main()
{
    ll k;
    cin >> k;
    if (k % 2 == 0)
    {
        cout << -1 << "\n";
    }
    else if (k % 5 == 0)
    {
        cout << -1 << "\n";
    }
    else
    {
        if (k % 7 == 0)
        {
            k /= 7;
        }
        k *= 9;
        ll n = phi(k);
        for (ll i = 1; i < n; i++)
        {
            if (pow(10, i, k) == 1)
            {
                n = i;
                break;
            }
        }
        cout << n << "\n";
    }
    return 0;
}