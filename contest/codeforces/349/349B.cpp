#include <bits/stdc++.h>

using namespace std;
const int MAX = 1e6 + 10;
int memo[MAX][10];
int arr[9];

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < 9; i++)
    {
        cin >> arr[i];
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i + arr[j] < MAX)
            {
                if (memo[i + arr[j]][9] < memo[i][9] + 1)
                {
                    for (int k = 0; k <= 8; k++)
                    {
                        memo[i + arr[j]][k] = memo[i][k] + (k == j);
                    }
                    memo[i + arr[j]][9] = memo[i][9] + 1;
                }
                else if (memo[i + arr[j]][9] == memo[i][9] + 1)
                {
                    bool is_greater = false;
                    for (int k = 8; k >= 0; k--)
                    {
                        if (memo[i + arr[j]][k] < memo[i][k] + (k == j))
                        {
                            is_greater = true;
                        }
                        else if (memo[i + arr[j]][k] > memo[i][k] + (k == j) && !is_greater)
                        {
                            is_greater = false;
                            break;
                        }
                    }
                    if (!is_greater)
                        continue;
                    for (int k = 0; k <= 8; k++)
                    {
                        memo[i + arr[j]][k] = memo[i][k] + (k == j);
                    }
                }
            }
        }
    }
    string s = "";
    for (int i = 8; i >= 0; i--)
    {
        for (int j = 0; j < memo[n][i]; j++)
        {
            s.push_back('0' + i + 1);
        }
    }
    if (s == "")
        cout << -1 << "\n";
    else
        cout << s << "\n";
}