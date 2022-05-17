#include <bits/stdc++.h>

using namespace std;
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        string a, b;
        cin >> a >> b;
        if (a.length() > b.length())
            swap(a, b);
        int max_overlap = 0;
        for (int i = 0; i < b.length(); i++)
        {
            for (int j = 0; j < a.length(); j++)
            {
                if (a[j] == b[i])
                {
                    int overlap = 0;
                    int start_a = j, start_b = i;
                    while (a[start_a] == b[start_b] && start_a < a.length() && start_b < b.length())
                    {
                        overlap++;
                        start_a++;
                        start_b++;
                    }

                    max_overlap = max(overlap, max_overlap);
                }
            }
        }
        int ans = a.length() + b.length() - max_overlap * 2;
        cout << ans << "\n";
    }
    return 0;
}