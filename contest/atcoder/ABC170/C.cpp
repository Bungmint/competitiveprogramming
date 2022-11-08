#include <bits/stdc++.h>

using namespace std;

int main()
{
    int x, n;
    cin >> x >> n;
    unordered_set<int> set1;
    for (int i = 0; i < n; i++)
    {
        int p;
        cin >> p;
        set1.insert(p);
    }
    int min_diff = 1e5;
    int j = x;
    while (set1.count(j) == 1)
    {
        j++;
    }
    min_diff = j;
    j = x;
    while (set1.count(j) == 1)
    {
        j--;
    }
    if (abs(x - min_diff) > abs(x - j))
    {
        min_diff = j;
    }
    else if (abs(x - min_diff) == abs(x - j))
    {
        min_diff = j;
    }

    cout << min_diff << "\n";
    return 0;
}