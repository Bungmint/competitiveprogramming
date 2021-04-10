#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> boys(n);
    vector<int> girls(m);

    int b, g;
    cin >> b;
    for (int i = 0; i < b; i++)
    {
        int tmp;
        cin >> tmp;
        boys[tmp] = 1;
    }
    cin >> g;
    for (int i = 0; i < g; i++)
    {
        int tmp;
        cin >> tmp;
        girls[tmp] = 1;
    }
    int days = lcm(m, n);
    for (int i = 0; i < 2 * days; i++)
    {
        boys[i % n] |= girls[i % m];
        girls[i % m] |= boys[i % n];
    }
    bool ok = true;
    for (int i = 0; i < n; i++)
    {
        if (boys[i] != 1)
            ok = false;
    }
    for (int i = 0; i < m; i++)
    {
        if (girls[i] != 1)
            ok = false;
    }
    if (ok)
        cout << "Yes"
             << "\n";
    else
        cout << "No"
             << "\n";
}