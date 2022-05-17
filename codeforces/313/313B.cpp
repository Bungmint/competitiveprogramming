#include <bits/stdc++.h>

using namespace std;
const int MAX = 1e5 + 7;
int dp[MAX];

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    string s;
    cin >> s;
    for (int i = 1; i < s.length(); i++)
    {
        dp[i] = dp[i - 1] + (s[i] == s[i - 1]);
    }
    int m;
    cin >> m;
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        int ans = dp[b - 1] - dp[a - 1];
        cout << ans << "\n";
    }
    return 0;
}