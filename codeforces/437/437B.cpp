#include <bits/stdc++.h>

using namespace std;

int lowbit(int x)
{
    if (x == 1)
        return 1;
    return pow(2, x - 1) * (x + 2);
}

int main()
{
    int sum, limit;
    cin >> sum >> limit;
    vector<int> bits;
    int max_pos = 0;
    for (int i = 1; i <= 32 - __builtin_clz(limit); i++)
    {
        bits.push_back((limit + pow(2, i - 1)) / pow(2, i));
        max_pos += bits[i - 1] * pow(2, i - 1);
    }
    if (max_pos < sum)
    {
        cout << -1 << "\n";
    }
    else
    {
        int size1 = 32 - __builtin_clz(limit);
        int ans_size = 0;
        vector<int> ans(size1);
        for (int i = size1 - 1; i >= 0; i--)
        {
            int d = sum / pow(2, i);
            ans[i] = min(d, bits[i]);
            ans_size += ans[i];
            sum -= ans[i] * pow(2, i);
        }
        cout << ans_size << "\n";
        for (int i = 0; i < size1; i++)
        {
            while (ans[i]--)
            {
                int num = pow(2, i) + ans[i] * pow(2, i + 1);
                cout << num << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}