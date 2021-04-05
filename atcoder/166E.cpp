#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MAX = 2e5 + 5;
ll heights_diff[MAX];
ll heights_sum[MAX];
pair<ll, ll> count_arr[MAX];

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ll n;
    cin >> n;
    ll counter = 0;
    for (ll i = 1; i <= n; i++)
    {
        ll tmp;
        cin >> tmp;
        heights_sum[i] = tmp + i;
        heights_diff[i] = i - tmp;
        if (tmp + i <= n)
            count_arr[tmp + i].first++;
        if (i - tmp >= 0)
            count_arr[i - tmp].second++;
    }
    for (ll i = 1; i <= n; i++)
    {
        counter += count_arr[i].first * count_arr[i].second;
    }

    cout << counter << "\n";
    return 0;
}