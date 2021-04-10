#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int lo = ceil((double)n / (double)4), hi = floor((double)2 * n / (double)7);
    if (lo > hi)
        cout << -1 << "\n";
    else
    {
        int x = 2 * n - 7 * hi, y = -n + 4 * hi;
        for (int i = 0; i < x; i++)
        {
            cout << 4;
        }
        for (int i = 0; i < y; i++)
        {
            cout << 7;
        }
        cout << "\n";
    }
}