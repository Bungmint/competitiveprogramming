#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);
    int t;
    cin >> t;

    while (t--)
    {
        int n, val;
        int prev = 0;
        vector<int> vec1, vec2;
        stack<int> storage1;
        queue<int> storage2;
        cin >> n;
        while (n--)
        {
            int x;
            cin >> x;
            if (x != prev)
            {
                for (int i = prev + 1; i < x; i++)
                {
                    storage1.push(i);
                    storage2.push(i);
                }
                vec1.push_back(x);
                vec2.push_back(x);
            }
            else
            {
                vec1.push_back(storage1.top());
                storage1.pop();
                vec2.push_back(storage2.front());
                storage2.pop();
            }
            prev = x;
        }
        for (auto j : vec2)
        {
            cout << j << " ";
        }
        cout << "\n";
        for (auto j : vec1)
        {
            cout << j << " ";
        }
        cout << "\n";
    }

    return 0;
}