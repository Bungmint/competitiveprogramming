#include <bits/stdc++.h>
const int MAX = 120;
using namespace std;
using ll = long long;
ll powers[MAX + 5];

int main()
{
    int x;
    cin >> x;
    for (ll i = 0; i <= MAX; i++)
    {
        powers[i] = pow(i, 5);
    }
    for (ll i = 0; i <= MAX; i++)
    {
        for (ll j = i + 1; j <= MAX; j++)
        {
            if (powers[i] + powers[j] == x)
            {
                cout << i << " " << -j << "\n";
                break;
            }
            else if (powers[j] - powers[i] == x)
            {
                cout << j << " " << i << "\n";
                break;
            }
        }
    }
    return 0;
}