#pragma GCC optimize("O3")
#pragma GCC target("sse4")
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
    if (n % 4 == 0 || n % 4 == 3)
    {
        cout << "YES\n";
        if (n % 4 == 0)
        {
            cout << n / 2 << "\n";
            for (int i = 1; i <= n / 4; i++)
            {
                cout << i << " " << n + 1 - i << " ";
            }
            cout << "\n";
            cout << n / 2 << "\n";
            for (int i = n / 4 + 1; i <= n / 2; i++)
            {
                cout << i << " " << n + 1 - i << " ";
            }
            cout << "\n";
        }
        else
        {
            cout << (n + 1) / 2 << "\n";
            for (int i = 1; i <= (n - 1) / 4 + 1; i++)
            {
                cout << i << " " << n - i << " ";
            }
            cout << "\n";
            cout << (n - 1) / 2 << "\n";
            for (int i = (n - 1) / 4 + 2; i <= (n - 1) / 2; i++)
            {
                cout << i << " " << n - i << " ";
            }
            cout << n << "\n";
        }
    }
    else
    {
        cout << "NO"
             << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}