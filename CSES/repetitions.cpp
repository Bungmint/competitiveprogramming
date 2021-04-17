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

void solve()
{
    string s;
    cin >> s;
    int ans = 1;
    int maximum = 1;
    char prev = '1';
    for (int i = 0; i < s.length(); i++)
    {
        if (prev == s[i])
            ans++;
        else
            ans = 1;
        maximum = max(ans, maximum);
        prev = s[i];
    }
    cout << maximum << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}