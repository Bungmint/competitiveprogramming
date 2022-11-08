#include <bits/stdc++.h>

using namespace std;
using ll = long long;
double dp[1 << 18][18];
double p[18][18];
int n;

double solve(ll mask, int i)
{
    double &ans = dp[mask][i];
    if (ans > -0.5)
        return ans;
    else if (mask == (1 << n) - 1)
        return ans = !i;
    ans = 0;
    for (int j = 0; j < n; j++)
    {
        if (((1 << j) & mask) == 0)
        {
            double cur = 0;
            cur += solve(mask | (1 << j), j) * p[j][i];
            cur += solve(mask | (1 << j), i) * p[i][j];
            ans = max(ans, cur);
        }
    }
    return ans;
}

int main()
{

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> p[i][j];
        }
    }
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = -1;
        }
    }
    double ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            ll mask = (1 << i) | (1 << j);
            double cur = 0;
            cur += solve(mask, i) * p[i][j];
            cur += solve(mask, j) * p[j][i];
            ans = max(ans, cur);
        }
    }
    if (n == 1)
        cout << 1 << "\n";
    else
        cout << ans << "\n";
}