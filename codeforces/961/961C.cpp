#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> zero_first(4);
    vector<int> one_first(4);
    for (int i = 0; i < 4; i++)
    {
        int o = 0;
        int z = 0;
        for (int j = 0; j < n; j++)
        {
            string s;
            cin >> s;
            for (int k = 0; k < n; k++)
            {
                if ((j + k) % 2 == 0 && s[k] == '1')
                    z++;
                if ((k + j + 1) % 2 == 0 && s[k] == '0')
                    z++;
                if ((k + j) % 2 == 0 && s[k] == '0')
                    o++;
                if ((k + j + 1) % 2 == 0 && s[k] == '1')
                    o++;
            }
        }
        zero_first[i] = z;
        one_first[i] = o;
    }
    int min1 = 1e7 + 7;
    min1 = min(min1, zero_first[0] + zero_first[1] + one_first[2] + one_first[3]);
    min1 = min(min1, zero_first[0] + zero_first[2] + one_first[1] + one_first[3]);
    min1 = min(min1, zero_first[0] + zero_first[3] + one_first[1] + one_first[2]);
    min1 = min(min1, zero_first[1] + zero_first[2] + one_first[0] + one_first[3]);
    min1 = min(min1, zero_first[1] + zero_first[3] + one_first[2] + one_first[0]);
    min1 = min(min1, zero_first[2] + zero_first[3] + one_first[1] + one_first[0]);
    cout << min1 << "\n";
}

int main()
{
    solve();
    return 0;
}