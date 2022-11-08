//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
ll arr[10007];

void precalc()
{
    arr[1] = 0;
    arr[2] = 6;
    for (ll i = 3; i <= 10000; i++)
    {
        arr[i] = arr[i - 1] + (i - 1) * (i - 1) * (2 * i - 1) - 4 * (i - 2) - 4 * (i - 1) + 4 + (2 * i - 1) * (i - 1);
    }
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cout << arr[i] << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    precalc();
    solve();
}