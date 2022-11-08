#include <bits/stdc++.h>

using namespace std;
const int MAX = 1e6 + 7;
int arr[MAX];

void precalc(int num)
{
    for (int j = 1; j <= num; j++)
    {
        for (int i = 1; i <= num / j; i++)
        {
            arr[i * j] += 1;
        }
    }
}

int main()
{
    int n;
    cin >> n;
    precalc(1e6 + 1);
    if (n < 2)
    {
        cout << 0 << endl;
    }
    long long ans = 0;
    for (int j = 1; j <= n - 1; j++)
    {
        ans += arr[j];
    }
    cout << ans << "\n";
    return 0;
}