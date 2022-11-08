#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll MAX = 2e5 + 7;
ll bit[MAX];

void add(int idx, ll val)
{
    for (++idx; idx < MAX; idx += idx & -idx)
        bit[idx] += val;
}

void range_add(int l, int r, ll val)
{
    add(l, val);
    add(r + 1, -val);
}

int point_query(int idx)
{
    ll ret = 0;
    for (++idx; idx > 0; idx -= idx & -idx)
        ret += bit[idx];
    return ret;
}
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    ll n, q;
    cin >> n >> q;
    vector<ll> arr(n);
    vector<ll> appearances(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    for (int i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        range_add(l, r, 1LL);
    }
    for (int i = 0; i < n; i++)
    {
        appearances[i] = point_query(i + 1);
    }
    sort(appearances.begin(), appearances.end());
    ll ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans += appearances[i] * arr[i];
    }
    cout << ans << "\n";
    return 0;
}