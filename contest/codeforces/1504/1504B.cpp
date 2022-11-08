#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        string a, b;
        cin >> a >> b;
        bool is_pos = true;
        int counter_a = 0;
        int counter_b = 0;
        int prev = 0;
        for (int i = 0; i < n; i++)
        {
            if (a[i] == '1')
                counter_a++;
            if (b[i] == '1')
                counter_b++;
            if (counter_a == (i + 1) / 2 && (i + 1) % 2 == 0)
            {
                if (counter_a != counter_b)
                {
                    is_pos = false;
                    break;
                }
                bool all_equal = true, all_diff = true;
                for (int j = prev; j <= i; j++)
                {
                    if (a[j] != b[j])
                    {
                        all_equal = false;
                        break;
                    }
                }
                for (int j = prev; j <= i; j++)
                {
                    if (a[j] == b[j])
                    {
                        all_diff = false;
                        break;
                    }
                }
                if (all_diff == false && all_equal == false)
                {
                    is_pos = false;
                    break;
                }
                prev = i + 1;
            }
        }
        if (prev != n - 1)
        {
            bool all_equal = true, all_diff = true;
            for (int j = prev; j <= n - 1; j++)
            {
                if (a[j] != b[j])
                {
                    all_equal = false;
                    break;
                }
            }
            for (int j = prev; j <= n - 1; j++)
            {
                if (a[j] == b[j])
                {
                    all_diff = false;
                    break;
                }
            }
            if (all_diff == false && all_equal == false)
            {
                is_pos = false;
            }
        }
        if (counter_a != counter_b)
            is_pos = false;
        if (is_pos)
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