#include <bits/stdc++.h>

using namespace std;

int main()
{
    vector<vector<int>> sq(3);
    vector<int> rows(3, 0);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int a;
            cin >> a;
            rows[i] += a;
            sq[i].push_back(a);
        }
    }
    int a, b, c;
    b = (rows[0] - rows[1] + rows[2]) / 2;
    a = rows[1] - rows[0] + b;
    c = rows[1] - rows[2] + b;

    sq[0][0] = a, sq[1][1] = b, sq[2][2] = c;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << sq[i][j] << " ";
        }
        cout << "\n";
    }
}