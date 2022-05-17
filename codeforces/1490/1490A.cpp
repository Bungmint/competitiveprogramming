#include <bits/stdc++.h>

using namespace std;

int calc(int x, int y)
{
    int ma = max(x, y);
    int mi = min(x, y);
    if (ma <= mi * 2)
        return 0;
    int counter = 0;
    while (ma > mi * 2)
    {
        mi *= 2;
        counter++;
    }
    return counter;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        int ans = 0;
        for (int i = 1; i < n; i++)
        {
            ans += calc(arr[i], arr[i - 1]);
        }
        cout << ans << "\n";
    }
}