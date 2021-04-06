#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    ll k;
    cin >> n >> k;
    ll cur_level = n;
    ll ans = -1;
    while (k && cur_level > 0)
    {
        ll mid = 1LL << (cur_level - 1);
        if (k == mid)
        {
            ans = cur_level;
            break;
        }
        else if (k > mid)
        {
            k -= mid;
        }
        cur_level--;
    }
    cout << ans << "\n";
}