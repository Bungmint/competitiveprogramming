#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;

    while (t--)
    {
        int n, temp;
        cin >> n;
        unordered_set<int> m1;
        while (n--)
        {
            cin >> temp;
            if (m1.count(temp) == 0)
            {
                m1.insert(temp);
            }
            else
            {
                m1.insert(temp + 1);
            }
        }
        cout << m1.size() << "\n";
    }
    return 0;
}