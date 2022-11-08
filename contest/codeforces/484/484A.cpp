#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        ll l, r;
        cin >> l >> r;
        if ((r & (r + 1)) == 0)
        {
            cout << r << "\n";
        }
        else
        {
            ll r_cp = r;
            vector<int> setbits;
            while (r_cp > 0)
            {
                setbits.push_back(63 - __builtin_clzll(r_cp));
                r_cp -= 1LL << (setbits[setbits.size() - 1]);
            }
            ll sum = -1;
            for (auto x : setbits)
            {
                sum += 1LL << (x);
                if (sum >= l)
                    break;
            }
            if (sum <= l)
            {
                sum = (__builtin_popcountll(r) > __builtin_popcountll(l)) ? r : sum = l;
            }
            if (__builtin_popcountll(sum) < __builtin_popcountll(r))
                sum = r;
            cout << sum << "\n";
        }
    }
    return 0;
}