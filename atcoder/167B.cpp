#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main()
{
    ll a, b, c, k;
    cin >> a >> b >> c >> k;
    if (a + b >= k)
    {
        cout << min(a, k) << "\n";
    }
    else
    {
        cout << a - (k - a - b) << "\n";
    }
    return 0;
}