#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    ll x;
    cin >> x;
    ll n = 100;
    int counter = 0;
    while (n < x)
    {
        n *= 1.01;
        counter++;
    }
    cout << counter << "\n";
    return 0;
}