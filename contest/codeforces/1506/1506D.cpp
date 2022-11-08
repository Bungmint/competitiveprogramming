#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;

    while (t--)
    {
        int n, cur, map_max, max_key;
        map_max = 0;
        unordered_map<int, int> m1;
        m1.reserve(1024);
        m1.max_load_factor(0.25);
        cin >> n;
        for (int x = n; x > 0; x--)
        {
            cin >> cur;
            m1[cur] = m1[cur] + 1;
            if (m1[cur] > map_max)
            {
                max_key = cur;
                map_max = m1[cur];
            }
        }
        if (map_max == n - map_max)
        {
            cout << 0 << "\n";
        }
        else if (map_max > n - map_max)
        {
            cout << map_max * 2 - n << "\n";
        }
        else
        {
            cout << n % 2 << "\n";
        }
    }

    return 0;
}