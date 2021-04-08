#include <bits/stdc++.h>

using namespace std;
const int MAX = 1e5 + 10;
int dp[MAX];
int arr[MAX];

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    unordered_set<int> track;
    track.reserve(1024);
    track.max_load_factor(0.25);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        track.insert(arr[i]);
        dp[i] = track.size();
    }
    while (m--)
    {
        int l;
        cin >> l;
        cout << dp[l - 1] << "\n";
    }
    return 0;
}