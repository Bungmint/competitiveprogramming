#include <iostream>
#include <string>
#include <chrono>

using namespace std;

int main()
{

    int t;
    string s;
    cin >> t;

    while (t--)
    {
        cin >> s;
        int len = s.length();
        bool zeros_before, ones_before;
        zeros_before = ones_before = false;
        int zeros_idx, ones_idx;
        ones_idx = -1;
        zeros_idx = -1;
        for (int i = 0; i < len - 1; i++)
        {
            if (s[i] == s[i + 1] && s[i] == '1' && !ones_before)
            {
                ones_before = true;
                ones_idx = i;
            }
            if (s[len - 1 - i] == s[len - 2 - i] && s[len - 1 - i] == '0' && !zeros_before)
            {
                zeros_before = true;
                zeros_idx = len - 1 - i;
            }
        }
        bool is_valid = true;
        if (ones_idx >= 0 && zeros_idx >= 0)
        {
            is_valid = ones_idx > zeros_idx;
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