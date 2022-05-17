#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> kangaroos(n);
    for (int i = 0; i < n; i++)
    {
        cin >> kangaroos[i];
    }
    sort(kangaroos.begin(), kangaroos.end());
    int j = n - 1, r, ans = -1;
    int counter = 0;
    while (j > (n - 1) / 2)
    {
        if (j == n - 1)
            r = j;
        else
            r = ans - 1;
        int l = 0;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (kangaroos[mid] * 2 <= kangaroos[j])
            {
                ans = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        if (ans != -1 && r >= 0)
            counter++;
        j--;
    }
    cout << n - counter << "\n";
    return 0;
}