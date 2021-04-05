#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, k, total;
    bool is_pos = false;
    total = 1;
    cin >> n >> k;
    while (n--)
    {
        int c;
        cin >> c;
        total = lcm(total, gcd(k, c));
        if (total % k == 0)
        {
            is_pos = true;
            break;
        }
    }
    if (is_pos)
    {
        cout << "YES"
             << "\n";
    }
    else
    {
        cout << "NO"
             << "\n";
    }

    return 0;
}