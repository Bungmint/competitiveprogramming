#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s, t;
    cin >> s >> t;
    int counter = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != t[i])
            counter++;
    }
    cout << counter << "\n";
    return 0;
}