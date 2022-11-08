#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
    ll n;

    bool has_zero = false;
    bool greater = false;
    cin >> n;
    vector<ll> vec(n);
    ll total = 1;
    for (int i = 0; i < n; i++)
    {
        ll tmp;
        cin >> tmp;
        vec[i] = tmp;
        if (tmp == 0)
            has_zero = true;
    }
    if (has_zero)
    {
        cout << 0 << endl;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (vec[i] <= 1000000000000000000 / total)
            {
                total *= vec[i];
            }
            else
            {
                greater = true;
                break;
            }
        }
        if (greater)
        {
            cout << -1 << endl;
        }
        else
        {
            cout << total << endl;
        }
    }
    return 0;
}