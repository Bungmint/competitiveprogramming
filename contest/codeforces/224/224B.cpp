#include <bits/stdc++.h>

using namespace std;
const int MAX = 1e5 + 7;
int arr[MAX];
int normal[MAX];

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, k;
    cin >> n >> k;
    memset(arr, 0, sizeof(arr));
    unordered_set<int> set1;
    set1.reserve(1024);
    set1.max_load_factor(0.25);
    for (int i = 0; i <= n - 1; i++)
    {
        int tmp;
        cin >> tmp;
        arr[tmp] += 1;
        normal[i] = tmp;
        set1.insert(tmp);
    }
    if (set1.size() < k)
    {
        cout << -1 << " " << -1 << "\n";
    }
    else
    {
        int cur_distinct = set1.size();
        int l = 0, r = n - 1;
        while (cur_distinct >= k)
        {
            arr[normal[r]]--;
            if (arr[normal[r]] == 0)
                cur_distinct--;
            r--;
        }
        r++;
        cur_distinct++;
        while (cur_distinct >= k && l <= r)
        {
            arr[normal[l]]--;
            if (arr[normal[l]] == 0)
                cur_distinct--;
            l++;
        }
        l--;
        cout << l + 1 << " " << r + 1 << "\n";
    }
    return 0;
}