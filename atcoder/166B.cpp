#include <bits/stdc++.h>

using namespace std;
unordered_set<int> set1;

int main()
{
    int n, k, d;
    cin >> n >> k;
    for (int i = 1; i <= k; i++)
    {
        cin >> d;
        for (int j = 1; j <= d; j++)
        {
            int a;
            cin >> a;
            set1.insert(a);
        }
    }
    cout << n - set1.size() << "\n";
    return 0;
}