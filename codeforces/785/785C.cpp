#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;

__int128 read()
{
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(__int128 x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
bool cmp(__int128 x, __int128 y) { return x > y; }

void solve()
{
    ll n, m;
    cin >> n >> m;
    if (n <= m)
        cout << n << "\n";
    else
    {
        __int128_t ans = -1;
        __int128_t l = 1, r = n;
        while (l <= r)
        {
            __int128_t mid = l + (r - l) / 2;
            if (mid * (mid + 1) / 2 >= n - m)
            {
                r = mid - 1;
                ans = mid;
            }
            else
                l = mid + 1;
        }
        ans += m;
        print(ans);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}