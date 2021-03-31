#include <bits/stdc++.h>
using ll = long long;
const ll mod = 1e9 + 7;
const ll exp_mod = 1e9 + 6;
using namespace std;
typedef vector<ll> vec;
typedef vector<vec> matrix;

matrix matrix_mul(const matrix &A, const matrix &B)
{
    ll n = A.size();
    matrix res(n, vec(n));
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            for (ll k = 0; k < n; k++)
            {
                res[i][j] += (A[i][k] % exp_mod) * (B[k][j] % exp_mod);
                res[i][j] %= exp_mod;
            }
        }
    }
    return res;
}
matrix power(const matrix &A, ll num)
{
    if (num == 1)
    {
        return A;
    }
    matrix result = power(A, num / 2);
    if (num % 2 == 0)
    {
        return matrix_mul(result, result);
    }
    else
    {
        return matrix_mul(A, matrix_mul(result, result));
    }
}

ll mod_power(ll x, ll k)
{
    if (k == 0)
    {
        return 1;
    }
    if (k == 1)
    {
        return x;
    }
    ll mid_pow = mod_power(x, k / 2);
    if (k % 2 == 0)
    {
        return (mid_pow * mid_pow) % mod;
    }
    return (((mid_pow * mid_pow) % mod) * x) % mod;
}

int main()
{
    matrix base{{0, 1, 0, 0, 0}, {0, 0, 1, 0, 0}, {1, 1, 1, 2, 0}, {0, 0, 0, 1, 1}, {0, 0, 0, 0, 1}};
    ll n, x, y, z, c;
    cin >> n >> x >> y >> z >> c;
    matrix final_mat = power(base, n - 1);
    ll total = 1;
    total *= (mod_power(x, final_mat[0][0]));
    total *= (mod_power(y, final_mat[0][1]));
    total %= mod;
    total *= mod_power(z, final_mat[0][2]);
    total %= mod;
    total *= mod_power(c, final_mat[0][3] + final_mat[0][4]);
    total %= mod;
    cout << total << "\n";
    return 0;
}