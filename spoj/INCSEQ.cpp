#include <bits/stdc++.h>
using ll = long long;
using namespace std;
int n, k, ans = 0, mod = 5000000;
ll tree[51][100000 + 10];

void update(int idx, int j, ll V)
{
    while (idx <= 100005)
    {
        tree[j][idx] = (tree[j][idx] + V) % mod;
        idx += idx & (-idx);
    }
}

ll query(int idx, int j)
{
    ll sum = 0;
    while (idx > 0)
    {
        sum = (sum + tree[j][idx]) % mod;
        idx -= idx & (-idx);
    }
    return sum;
}

int main()
{
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    scanf("%d%d", &n, &k);
    for (int j = 1; j <= n; j++)
    {
        int a;
        scanf("%d", &a);
        a++;
        for (int i = 1; i <= k; i++)
        {
            ll p = i == 1 ? 1 : query(a - 1, i - 1);
            update(a, i, p);
            if (i == k)
                ans = (ans + p) % mod;
        }
    }
    cout << ans << endl;
    return 0;
}