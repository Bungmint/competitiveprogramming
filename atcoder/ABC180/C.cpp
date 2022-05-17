#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
    ll n;
    cin >> n;
    vector<ll> factors;
    for (ll i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            factors.push_back(i);
            if (i != n / i)
            {
                factors.push_back(n / i);
            }
        }
    }
    sort(factors.begin(), factors.end());
    for (int i = 0; i < factors.size(); i++)
    {
        cout << factors[i] << "\n";
    }
}