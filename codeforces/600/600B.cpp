#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(n), b(m);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].first;
        a[i].second = i;
    }
    for (int j = 0; j < m; j++)
    {
        cin >> b[j].first;
        b[j].second = j;
    }
    sort(all(a));
    sort(all(b));
    int j = 0;
    for (int i = 0; i < m; i++)
    {
        while (a[j].first <= b[i].first && j < n)
        {
            j++;
        }
        b[i].first = j;
    }
    sort(all(b), [](auto &left, auto &right) { return left.second < right.second; });
    for (auto x : b)
    {
        cout << x.first << " ";
    }
    cout << "\n";
    return 0;
}