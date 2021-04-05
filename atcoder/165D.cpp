#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
    ll a, b, n;
    cin >> a >> b >> n;
    ll alpha = min(b - 1, n);
    cout << floor(a * alpha / b) << "\n";
    return 0;
}