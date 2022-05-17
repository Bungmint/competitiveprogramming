#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<int> balls(n);
    unordered_set<int> b;
    b.reserve(1024);
    b.max_load_factor(0.25);
    for (int i = 0; i < n; i++)
    {
        cin >> balls[i];
        b.insert(balls[i]);
    }
    bool ok = false;
    for (int i = 0; i < n; i++)
    {
        if (b.count(balls[i] + 1) && b.count(balls[i] + 2))
        {
            ok = true;
            break;
        }
    }
    if (ok)
        cout << "YES"
             << "\n";
    else
        cout << "NO"
             << "\n";
}