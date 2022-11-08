#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        ll ans = 0;
        for (int i = 0; i < 63; ++i)
        {
            if (n & (1ll << i))
            {
                ans += (1ll << (i + 1)) - 1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}