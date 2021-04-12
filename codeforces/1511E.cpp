#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 998244353;
const int MAX = 3e5 + 10;
ll arr[MAX];

ll mod_pow(ll base, ll exp)
{
    if (exp == 0)
        return 1;
    if (exp == 1)
        return base;
    ll mid = mod_pow(base, exp / 2);
    if (exp % 2 == 0)
        return (mid * mid) % MOD;
    else
        return (((mid * mid) % MOD) * base) % MOD;
}

void precalc()
{
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 1;
    for (int i = 3; i < MAX; i++)
    {
        arr[i] = (arr[i - 1] + arr[i - 2] * 2 + mod_pow(2, i - 2)) % MOD;
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;
    ll ans = 0;
    ll total_white = 0;
    vector<vector<int>> mat(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++)
        {
            mat[i][j] = (s[j] == 'o');
            if (s[j] == 'o')
                total_white++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        int j = 0;
        while (j < m)
        {
            if (mat[i][j] == 1)
            {
                ll leng = 1;
                while (j + 1 < m && mat[i][j + 1] == 1)
                {
                    leng++;
                    j++;
                }
                ans = (ans + (arr[leng] * mod_pow(2LL, total_white - leng)) % MOD) % MOD;
            }
            j++;
        }
    }
    for (int i = 0; i < m; i++)
    {
        int j = 0;
        while (j < n)
        {
            if (mat[j][i] == 1)
            {
                ll leng = 1;
                while (j + 1 < n && mat[j + 1][i] == 1)
                {
                    j++;
                    leng++;
                }
                ans = (ans + (arr[leng] * mod_pow(2LL, total_white - leng)) % MOD) % MOD;
            }
            j++;
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    precalc();
    solve();
}