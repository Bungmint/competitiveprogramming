#include <bits/stdc++.h>

using namespace std;
using ll = long long;
ll B1[100000 + 7];
ll B2[100000 + 7];

void add(ll b[], int idx, ll x)
{
    while (idx <= 100005)
    {
        b[idx] += x;
        idx += idx & -idx;
    }
}

void range_add(int l, int r, ll x)
{
    add(B1, l, x);
    add(B1, r + 1, -x);
    add(B2, l, x * (l - 1));
    add(B2, r + 1, -x * r);
}

ll sum(ll b[], int idx)
{
    ll total = 0;
    while (idx > 0)
    {
        total += b[idx];
        idx -= idx & (-idx);
    }
    return total;
}

ll prefix_sum(int idx)
{
    return sum(B1, idx) * idx - sum(B2, idx);
}

ll range_sum(int l, int r)
{
    return prefix_sum(r) - prefix_sum(l - 1);
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        memset(B1, 0, sizeof(B1));
        memset(B2, 0, sizeof(B2));
        int n, c;
        cin >> n >> c;
        for (int i = 1; i <= c; i++)
        {
            int task, p, q;
            cin >> task >> p >> q;
            switch (task)
            {
            case 0:
                ll v;
                cin >> v;
                range_add(p, q, v);
                break;
            case 1:
                ll ans = range_sum(p, q);
                cout << ans << "\n";
                break;
            }
        }
    }
    return 0;
}