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
    int n;
    cin >> n;
    bool is_pos = false;
    if (n % 2 == 1)
    {
        if (n == 1 || abs(n - 2) > 1)
            is_pos = true;
        if (is_pos)
        {
            for (int i = 1; i <= (n + 1) / 2; i++)
            {
                cout << 2 * i - 1 << " ";
            }
            for (int i = 1; i < (n + 1) / 2; i++)
            {
                cout << 2 * i << " ";
            }
            cout << "\n";
        }
    }
    else
    {
        if (abs(n - 1) > 1)
            is_pos = true;
        if (is_pos)
        {
            for (int i = 1; i <= n / 2; i++)
                cout << 2 * i << " ";
            for (int i = 1; i <= n / 2; i++)
                cout << 2 * i - 1 << " ";
        }
        cout << "\n";
    }
    if (!is_pos)
        cout << "NO SOLUTION"
             << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}