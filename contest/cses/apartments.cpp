
#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;

void solve()
{
    int n, m;
    ll k;
    cin >> n >> m >> k;
    vector<ll> applicants(n);
    vector<ll> rooms(m);
    for (int i = 0; i < n; i++)
    {
        cin >> applicants[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> rooms[i];
    }
    sort(all(applicants));
    sort(all(rooms));
    int i = 0, j = 0, ans = 0;
    while (i < n && j < m)
    {
        if (abs(applicants[i] - rooms[j]) <= k)
        {
            ans++;
            i++;
            j++;
        }
        else
        {
            if (applicants[i] > rooms[j] + k)
                j++;
            else if (applicants[i] < rooms[j] - k)
                i++;
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}