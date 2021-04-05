#include <bits/stdc++.h>

using namespace std;
typedef vector<char> vec;
typedef vector<vec> matrix;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        bool is_valid = true;
        cin >> n;
        matrix mat(n, vec(n));
        for (int i = 0; i < n; i++)
        {
            string s;
            cin >> s;
            for (int j = 0; j < n; j++)
            {
                mat[i][j] = s[j];
            }
        }
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - 1; j++)
            {
                if (mat[i][j] == '1' && (mat[i][j + 1] == '0' && mat[i + 1][j] == '0'))
                {
                    is_valid = false;
                }
            }
        }
        if (is_valid)
        {
            cout << "YES"
                 << "\n";
        }
        else
        {
            cout << "NO"
                 << "\n";
        }
    }
    return 0;
}