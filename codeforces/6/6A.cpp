#include <bits/stdc++.h>

using namespace std;

int main()
{
    vector<int> arr(4);
    bool is_pos = false;
    bool is_degen = true;
    for (int i = 0; i < 4; i++)
    {
        cin >> arr[i];
    }
    for (int i = 0; i < 4; i++)
    {
        int a = arr[i], b = arr[(i + 1) % 4], c = arr[(i + 2) % 4];
        int maximum = max({a, b, c});
        int minimum = min({a, b, c});
        int mid = a + b + c - maximum - minimum;
        if (maximum > minimum + mid)
            continue;
        else if (maximum == minimum + mid)
            is_pos = true;
        else
        {
            is_pos = true;
            is_degen = false;
        }
    }
    if (is_pos)
    {
        if (is_degen)
            cout << "SEGMENT"
                 << "\n";
        else
            cout << "TRIANGLE"
                 << "\n";
    }
    else
        cout << "IMPOSSIBLE"
             << "\n";
}