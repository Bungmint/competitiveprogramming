#include <bits/stdc++.h>

using namespace std;
const int MAX = 105;
int arr[MAX];

int height_tree(vector<int> &vec, int l, int r, int counter)
{
    if (l > r)
        return 0;
    if (l == r)
    {
        arr[l] = counter;
        return 1;
    }
    int max_idx = 0;
    int max_num = 0;
    for (int i = l; i <= r; i++)
    {
        if (max_num < vec[i])
        {
            max_idx = i;
            max_num = vec[i];
        }
    }
    int ans = 1 + max(height_tree(vec, l, max_idx - 1, counter + 1), height_tree(vec, max_idx + 1, r, counter + 1));
    arr[max_idx] = counter;
    return ans;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        memset(arr, 0, sizeof(arr));
        int n;
        cin >> n;
        vector<int> perms(n);
        int max_idx;
        for (int i = 0; i < n; i++)
        {
            cin >> perms[i];
        }
        int h = height_tree(perms, 0, n - 1, 0);
        for (int i = 0; i < n; i++)
        {
            cout << arr[i] << "\n";
        }
    }
}