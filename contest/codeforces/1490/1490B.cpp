#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> vec(n);
        int a = 0, b = 0, c = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> vec[i];
            if (vec[i] % 3 == 0)
                a++;
            else if (vec[i] % 3 == 1)
                b++;
            else
                c++;
        }
        int target = (a + b + c) / 3;
        if (a == b && b == c)
        {
            cout << 0 << "\n";
        }
        else
        {
            int ans = 0;
            while (a != b || b != c)
            {
                if (a > target)
                {
                    ans += (a - target);
                    b += (a - target);
                    a = target;
                }
                if (b > target)
                {
                    ans += (b - target);
                    c += (b - target);
                    b = target;
                }
                if (c > target)
                {
                    ans += (c - target);
                    a += (c - target);
                    c = target;
                }
            }
            cout << ans << "\n";
        }
    }
}