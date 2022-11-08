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
    int n, t;
    string s;
    cin >> n >> t >> s;
    while (t--)
    {
        int prev = -1;
        for (int i = 1; i < n; i++)
        {
            if (s[i - 1] == 'B' && s[i] == 'G' && prev != i - 1)
            {
                swap(s[i - 1], s[i]);
                prev = i;
            }
        }
    }
    cout << s << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}