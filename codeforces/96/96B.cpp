#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<ll> even_47(int leng)
{
    int half = leng / 2;
    vector<ll> res;
    set<string> set1;
    string s = "";
    for (int i = 0; i < half; i++)
    {
        s += '4';
    }
    for (int i = 0; i < half; i++)
    {
        s += '7';
    }
    do
    {
        set1.insert(s);
    } while (next_permutation(s.begin(), s.end()));
    for (auto x : set1)
    {
        res.push_back(stoll(x));
    }
    return res;
}

int main()
{
    int n;
    cin >> n;
    int num_digits = 1 + floor(log10(n));
    if (num_digits % 2 != 0)
    {
        ll ans = 0;
        for (int i = 0; i < (num_digits + 1) / 2; i++)
        {
            ans += 7LL * pow(10, i);
        }
        for (int i = (num_digits + 1) / 2; i < (num_digits + 1); i++)
        {
            ans += 4LL * pow(10, i);
        }
        cout << ans << "\n";
    }
    else
    {
        ll ans = -1e10;
        vector<ll> options = even_47(num_digits);
        for (auto x : options)
        {
            if (x >= n && abs(n - ans) > abs(x - n))
            {
                ans = x;
            }
        }
        if (ans == -1e10)
        {
            ll ans = 0;
            for (int i = 0; i < (num_digits + 2) / 2; i++)
            {
                ans += 7LL * pow(10, i);
            }
            for (int i = (num_digits + 2) / 2; i < (num_digits + 2); i++)
            {
                ans += 4LL * pow(10, i);
            }
            cout << ans << "\n";
        }
        else
        {
            cout << ans << "\n";
        }
    }
}