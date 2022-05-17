#include <bits/stdc++.h>

using namespace std;

vector<int> prime_factor(int n)
{
    vector<int> res;
    for (int i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            res.push_back(i);
        }
    }
    int cur = res.size();
    for (int i = 0; i < cur; i++)
    {
        res.push_back(n / res[i]);
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<int> factors = prime_factor(n);
    vector<int> sculp(n);
    for (int i = 0; i < n; i++)
    {
        cin >> sculp[i];
    }
    int ans = -1e9;
    for (int i = 0; i < (int)factors.size(); i++)
    {
        if (factors[i] >= (n + 1) / 2)
            continue;
        for (int j = 0; j < factors[i]; j++)
        {
            int tmp = 0;
            for (int k = 0; k < n / factors[i]; k++)
            {
                tmp += sculp[(k * factors[i] + j) % n];
            }
            ans = max(ans, tmp);
        }
    }
    cout << ans << "\n";
    return 0;
}