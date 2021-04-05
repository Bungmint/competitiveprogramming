#include <bits/stdc++.h>
using ll = long long;
using namespace std;

pair<ll, ll> max_tri(ll num)
{
    ll total = 0, counter = 1;
    while (total < num)
    {
        total += counter;
        counter++;
    }
    return {total - counter + 1, counter - 1};
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;

    while (t--)
    {
        ll n, k;
        cin >> n >> k;
        string s;
        for (ll i = 0; i < n; i++)
        {
            s.push_back('a');
        }
        pair<ll, ll> num = max_tri(k);
        ll diff = k - num.first;
        s[s.length() - 1 - num.second] = 'b';
        s[s.length() - diff] = 'b';
        cout << s << "\n";
    }
    return 0;
}