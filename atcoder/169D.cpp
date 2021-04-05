#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll MAX = 1e6 + 10;
vector<ll> primes;
void sieve(ll num)
{
    bool A[num + 1];
    memset(A, true, sizeof(A));
    A[0] = false;
    A[1] = false;
    for (ll i = 2; i <= num; i++)
    {
        if (A[i])
        {
            for (ll j = i * i; j <= num; j += i)
            {
                A[j] = false;
            }
        }
    }
    for (ll i = 0; i <= num; i++)
    {
        if (A[i])
            primes.push_back(i);
    }
}

ll big_tri(ll x)
{
    return floor((-1 + sqrt(1 + 8 * x)) / 2);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;
    sieve(MAX);
    ll counter = 0;
    for (auto x : primes)
    {
        ll c = 0;
        while (n % x == 0)
        {
            n /= x;
            c++;
        }
        counter += big_tri(c);
    }
    if (n > 1)
        counter += 1;
    cout << counter << "\n";
    return 0;
}