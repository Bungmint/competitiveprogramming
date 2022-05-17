#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, a, b;
    cin >> n;
    int years[102];
    for (int i = 1; i <= n - 1; i++)
    {
        cin >> years[i];
    }
    cin >> a >> b;
    int ans = 0;
    while (a != b)
    {
        ans += years[a];
        a++;
    }
    cout << ans << "\n";
    return 0;
}