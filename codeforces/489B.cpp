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
    int n, m;
    cin >> n;
    vector<int> boys(n);
    for (int i = 0; i < n; i++)
        cin >> boys[i];
    cin >> m;
    vector<int> girls(m);
    for (int i = 0; i < m; i++)
        cin >> girls[i];
    sort(all(boys));
    sort(all(girls));
    int i = 0;
    int j = 0;
    int counter = 0;
    while (i < n && j < m)
    {
        if (abs(boys[i] - girls[j]) <= 1)
        {
            counter++;
            i++;
            j++;
        }
        if (girls[j] > boys[i] + 1)
            i++;
        if (boys[i] > girls[j] + 1)
            j++;
    }
    cout << counter << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}