#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, temp;
    vector<int> vec;
    cin >> n;
    while (n--)
    {
        cin >> temp;
        vec.push_back(temp % 2);
    }
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i] != vec[i - 1])
        {
            if (i == 1)
            {
                if (vec[vec.size() - 1] != vec[1])
                {
                    cout << 2 << "\n";
                    break;
                }
                else
                {
                    cout << 1 << "\n";
                    break;
                }
            }
            else
            {
                if (vec[0] != vec[i])
                {
                    cout << i + 1 << "\n";
                    break;
                }
                else
                {
                    cout << i << "\n";
                    break;
                }
            }
        }
    }
    return 0;
}