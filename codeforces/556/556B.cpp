#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> gears(n);
    for (int i = 0; i < n; i++)
    {
        cin >> gears[i];
    }
    int first_gear = gears[0];
    for (int i = 0; i < n; i++)
    {
        if (i & 1)
        {
            gears[i] = (gears[i] - (n - first_gear) + n) % n;
        }
        else
        {
            gears[i] = (gears[i] + (n - first_gear)) % n;
        }
    }
    bool ok = true;
    for (int i = 0; i < n; i++)
    {
        if (gears[i] != i)
        {
            ok = false;
            break;
        }
    }
    if (ok)
        cout << "Yes"
             << "\n";
    else
        cout << "No"
             << "\n";
}