#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int switch1 = 1;
    while (n--)
    {
        int a;
        cin >> a;
        if (a % 2 == 0)
        {
            cout << a / 2 << "\n";
        }
        else
        {
            if (switch1)
            {
                if (a > 0)
                {
                    cout << a / 2 << "\n";
                }
                else
                {
                    cout << a / 2 - 1 << "\n";
                }
                switch1 += 1;
                switch1 %= 2;
            }
            else
            {
                if (a > 0)
                {
                    cout << a / 2 + 1 << "\n";
                }
                else
                {
                    cout << a / 2 << "\n";
                }
                switch1 += 1;
                switch1 %= 2;
            }
        }
    }
    return 0;
}