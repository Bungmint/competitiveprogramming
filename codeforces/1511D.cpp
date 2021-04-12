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
    int n, k;
    cin >> n >> k;
    string ans = "";
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int i = 0;
    while (ans.length() < n)
    {
        i %= k;
        int tog = 0;
        int j = i + 1;
        ans.push_back(alphabet[i]);
        while (ans.length() < n && j < k)
        {
            if (tog)
            {
                ans.push_back(alphabet[j]);
                j++;
                tog += 1;
                tog %= 2;
            }
            else
            {
                ans.push_back(alphabet[i]);
                tog += 1;
                tog %= 2;
            }
        }
        i++;
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}