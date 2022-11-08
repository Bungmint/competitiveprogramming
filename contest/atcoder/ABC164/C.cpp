#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    unordered_set<string> set1;
    int n;
    cin >> n;
    while (n--)
    {
        string s;
        cin >> s;
        set1.insert(s);
    }
    cout << set1.size() << "\n";
    return 0;
}