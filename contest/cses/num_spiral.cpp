//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;

void solve()
{
    ll y, x;
    cin >> y >> x;
    if (y >= x)
    {
        if ((y - 1) % 2 == 0)
        {
            cout << (y - 1) * (y - 1) + x << "\n";
        }
        else
        {
            cout << y * y - x + 1 << "\n";
        }
    }
    else
    {
        if ((x - 1) % 2 == 0)
        {
            cout << x * x - y + 1 << "\n";
        }
        else
        {
            cout << (x - 1) * (x - 1) + y << "\n";
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}