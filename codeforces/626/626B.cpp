#include <bits/stdc++.h>

using namespace std;
int memo[201][201][201];

int cards(int a, int b, int c)
{
    if (memo[a][b][c] != -1)
        return memo[a][b][c];
    if (a + b + c == 1)
    {
        if (a)
        {
            memo[a][b][c] = 1;
            return 1;
        }
        else if (b)
        {
            memo[a][b][c] = 2;
            return 2;
        }
        else
        {
            memo[a][b][c] = 4;
            return 4;
        }
    }
    int ans = 0;
    if (a >= 2)
        ans |= cards(a - 1, b, c);
    if (b >= 2)
        ans |= cards(a, b - 1, c);
    if (c >= 2)
        ans |= cards(a, b, c - 1);
    if (a + b >= 2 && a >= 1 && b >= 1)
        ans |= cards(a - 1, b - 1, c + 1);
    if (b + c >= 2 && b >= 1 && c >= 1)
        ans |= cards(a + 1, b - 1, c - 1);
    if (c + a >= 2 && c >= 1 && a >= 1)
        ans |= cards(a - 1, b + 1, c - 1);
    memo[a][b][c] = ans;
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int r, g, b, n;
    r = 0, g = 0, b = 0;
    string s;
    cin >> n >> s;
    memset(memo, -1, sizeof(memo));
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'R')
            r++;
        else if (s[i] == 'G')
            g++;
        else
            b++;
    }

    int res = cards(r, g, b);
    if (res & 4)
        cout << "B";
    if (res & 2)
        cout << "G";
    if (res & 1)
        cout << "R";

    cout << "\n";
    return 0;
}