#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> cowbells(n);
    for (int i = 0; i < n; i++)
    {
        cin >> cowbells[i];
    }
    int l = 0, r = n - 1;
    int pos = -1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if ((mid + 2) / 2 <= k - (n - mid - 1))
        {
            pos = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    int res = 0;
    if (pos % 2 == 0)
    {
        res = cowbells[pos];
        for (int i = 0; i <= pos - 1; i++)
        {
            res = max(res, cowbells[i] + cowbells[pos - i]);
        }
    }
    else
    {
        for (int i = 0; i <= pos; i++)
        {
            res = max(res, cowbells[i] + cowbells[pos - i]);
        }
    }
    res = max(res, cowbells[cowbells.size() - 1]);
    cout << res << "\n";
}