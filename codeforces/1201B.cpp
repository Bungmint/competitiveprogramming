#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;

void solve()
{
    int n;
    cin >> n;
    vector<ll> arr(n);
    ll sum = 0;
    ll maximum = -1;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        sum += arr[i];
        maximum = max(maximum, arr[i]);
    }
    if (sum % 2 || maximum > sum - maximum)
        cout << "NO"
             << "\n";
    else
        cout << "YES"
             << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}