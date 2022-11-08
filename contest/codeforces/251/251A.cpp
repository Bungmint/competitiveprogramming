#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    long long d;
    cin >> n >> d;
    vector<long long> x_coord(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x_coord[i];
    }
    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        long long cur_val = x_coord[i];
        int l = i + 1, r = n - 1;
        long long res = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (x_coord[mid] <= d + x_coord[i])
            {
                res = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        if (res == -1)
            continue;
        else
            ans += (res - i) * (res - i - 1) / 2;
    }
    cout << ans << "\n";
}