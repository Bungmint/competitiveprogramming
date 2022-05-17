#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;

ll proper_div(ll x, ll y)
{
    ll ans = x / y;
    if (x % y != 0)
        ans++;
    if (x < 0)
        return 0;
    return ans;
}

void solve()
{
    int n;
    ll c;
    cin >> n >> c;
    vector<ll> salary(n);
    vector<ll> ed(n - 1);
    ll ed_days = 0;

    vector<ll> days(n);
    vector<ll> start_val(n);
    for (int i = 0; i < n; i++)
    {
        cin >> salary[i];
    }
    for (int i = 0; i < n - 1; i++)
    {
        cin >> ed[i];
    }
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
            start_val[i] = 0;
        else
            start_val[i] = start_val[i - 1] + max(0LL, proper_div(ed[i - 1] - start_val[i - 1], salary[i - 1])) * salary[i - 1] - ed[i - 1];
        days[i] = max(0LL, proper_div(c - start_val[i], salary[i])) + ed_days;

        if (i != n - 1)
        {
            ed_days += 1 + max(0LL, proper_div(ed[i] - start_val[i], salary[i]));
        }
    }
    sort(all(days));
    cout << days[0] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}