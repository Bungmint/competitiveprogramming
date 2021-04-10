#include <bits/stdc++.h>

using namespace std;
const int N = 5e6; // Only advised to use it under 1e7 (More Memory)
int lp[N + 1];
vector<int> pr;
int memo[N + 1];
int prefixsum[N + 1];
void linsieve()
{
    for (int i = 2; i <= N; i++)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
        {
            lp[i * pr[j]] = pr[j];
        }
    }
}

int precalc(int x)
{
    if (memo[x] != -1)
        return memo[x];
    if (x == lp[x])
    {
        memo[x] = 1;
        return 1;
    }
    int s = precalc(x / lp[x]) + 1;
    memo[x] = s;
    return memo[x];
}

void precalc_every()
{
    for (int i = 2; i <= N; i++)
    {
        precalc(i);
    }
}

void prefix()
{
    for (int i = 1; i <= N; i++)
    {
        if (i == 1)
            prefixsum[i] = 0;
        else
            prefixsum[i] = prefixsum[i - 1] + memo[i];
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    linsieve();
    memset(memo, -1, sizeof(memo));
    precalc_every();
    prefix();
    int t;
    cin >> t;
    while (t--)
    {
        int a, b;
        cin >> a >> b;
        cout << prefixsum[a] - prefixsum[b] << "\n";
    }
}