#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    long long ans = 0;
    long long cur_max = 0;
    for (int i = 0; i < n; i++)
    {
        long long cur;
        cin >> cur;
        ans += max(cur_max - cur, 0ll);
        cur_max = max(cur_max, cur);
    }
    cout << ans << "\n";
    return 0;
}