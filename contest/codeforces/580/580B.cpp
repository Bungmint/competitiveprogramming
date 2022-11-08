#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
using namespace std;
using ll = long long;

int main()
{
    ll n;
    ll d;
    cin >> n >> d;
    vector<pair<ll, ll>> friends(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> friends[i].first >> friends[i].second;
    }
    sort(all(friends));
    vector<ll> friendship_sum(n);
    for (ll i = 0; i < n; i++)
    {
        if (i == 0)
            friendship_sum[i] = friends[i].second;
        else
            friendship_sum[i] = friendship_sum[i - 1] + friends[i].second;
    }
    ll final_ans = 0;

    for (ll i = 0; i < n; i++)
    {
        ll L = i, R = n - 1, ans = -1, target = friends[i].first + d - 1;
        while (L <= R)
        {
            ll mid = L + (R - L) / 2;
            if (friends[mid].first <= target)
            {
                ans = mid;
                L = mid + 1;
            }
            else
            {
                R = mid - 1;
            }
        }
        if (ans == -1)
            continue;
        if (i == 0)
            final_ans = max(final_ans, friendship_sum[ans]);
        else
            final_ans = max(final_ans, friendship_sum[ans] - friendship_sum[i - 1]);
    }
    cout << final_ans << "\n";
    return 0;
}