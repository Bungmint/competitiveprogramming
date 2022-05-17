#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> res(n, vector<char>(m));
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++)
        {
            if (s[j] == '.')
            {
                if ((i + j) % 2 == 0)
                {
                    res[i][j] = 'W';
                }
                else
                {
                    res[i][j] = 'B';
                }
            }
            else
            {
                res[i][j] = '-';
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << res[i][j];
        }
        cout << "\n";
    }
    return 0;
}