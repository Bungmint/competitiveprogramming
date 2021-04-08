#include <bits/stdc++.h>

using namespace std;
const int MOD = 1e8;
int k1, k2;
int memo[101][101][11][11];

int C(int f, int h, int kf, int kh)
{
    if (memo[f][h][kf][kh] != -1)
        return memo[f][h][kf][kh];
    if (f + h == 0)
        return 1;
    int ans = 0;
    if (f > 0 && kf > 0)
        ans += C(f - 1, h, kf - 1, k2);
    ans %= MOD;
    if (h > 0 && kh > 0)
        ans += C(f, h - 1, k1, kh - 1);
    ans %= MOD;
    memo[f][h][kf][kh] = ans;
    return ans;
}

int main()
{
    memset(memo, -1, sizeof(memo));
    int n1, n2;
    cin >> n1 >> n2 >> k1 >> k2;
    cout << C(n1, n2, k1, k2) << "\n";
    return 0;
}