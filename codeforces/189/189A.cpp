#include <bits/stdc++.h>
using namespace std;
const int MAX = 4005;
int arr[MAX];

int main()
{
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    for (int i = 1; i <= n; i++)
    {
        arr[i] = 0;
    }
    int temp = c, sum = a + b + c;
    c = max({a, b, c});
    a = min({a, b, temp});
    b = sum - a - c;
    arr[a] = arr[b] = arr[c] = 1;
    for (int i = a; i <= n; i++)
    {
        if (i == a)
            continue;
        int s_a, s_b, s_c;
        s_a = i - a;
        s_b = i - b;
        s_c = i - c;
        if (s_b < 0)
        {
            if (arr[s_a] == 0)
                continue;
            arr[i] = arr[s_a] + 1;
        }
        else if (s_c < 0)
        {
            if (arr[s_a] == 0 && arr[s_b] == 0)
            {
                continue;
            }
            else
            {
                arr[i] = max(arr[s_a], arr[s_b]) + 1;
            }
        }
        else
        {
            if (arr[s_a] == 0 && arr[s_b] == 0 && arr[s_c] == 0)
            {
                continue;
            }
            else
            {
                arr[i] = max({arr[s_a], arr[s_b], arr[s_c]}) + 1;
            }
        }
    }
    cout << arr[n] << "\n";
    return 0;
}