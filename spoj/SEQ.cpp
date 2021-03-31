#include <bits/stdc++.h>
using ll = long long int;
#define mod 1000000000ll
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
                res[i][j] += (A[i][k] % mod) * (B[k][j] % mod);
                res[i][j] %= mod;
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

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        ll k, temp, n;
        vec b;
        vec c;
        cin >> k;
        matrix mat(k, vec(k));
        for (ll x = 0; x < k; x++)
        {
            cin >> temp;
            b.push_back(temp % mod);
        }
        for (ll x = 0; x < k; x++)
        {
            cin >> temp;
            c.push_back(temp % mod);
            mat[k - 1][k - 1 - x] = temp % mod;
        }
        for (ll x = 0; x < k - 1; x++)
        {
            mat[x][x + 1] = 1ll;
        }
        cin >> n;
        if (n <= k)
        {
            cout << b[n - 1] << "\n";
        }
        else
        {
            ll diff = n - k;
            matrix final_mat = power(mat, diff);
            ll total = 0;
            for (ll x = 0; x < k; x++)
            {
                total += (b[x] % mod) * (final_mat[k - 1][x] % mod);
                total %= mod;
            }
            cout << total << "\n";
        }
    }

    return 0;
}