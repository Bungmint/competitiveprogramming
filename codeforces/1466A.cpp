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
        unordered_set<int> s;
        cin >> n;
        int arr[n];
        for (int i = 0; i < n; i++)
        {
            cin >> temp;
            arr[i] = temp;
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                s.insert(arr[j] - arr[i]);
            }
        }
        cout << s.size() << "\n";
    }
    return 0;
}