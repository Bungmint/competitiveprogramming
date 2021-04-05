#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }
    sort(all(vec));
    long long ans = 0;
    for (int i = 1; i < n; i++)
    {
        ans += vec[vec.size() - 1 - floor(i / 2)];
    }
    cout << ans << "\n";

    return 0;
}