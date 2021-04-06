#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, l;
    cin >> n >> l;
    vector<int> lights(n);
    for (int i = 0; i < n; i++)
    {
        cin >> lights[i];
    }
    sort(lights.begin(), lights.end());
    int diff = 0;
    for (int i = 1; i < n; i++)
    {
        diff = max(diff, lights[i] - lights[i - 1]);
    }
    diff = max(diff, 2 * lights[0]);
    diff = max(diff, (l - lights[lights.size() - 1]) * 2);
    if (diff % 2 == 0)
        cout << diff / 2 << "\n";
    else
    {
        double x = ((double)diff / (double)2);
        cout << setprecision(16);
        cout << x << "\n";
    }
    return 0;
}