#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    cin >> s;
    int leng = s.length();
    char c = 'a';
    for (int i = 0; i < leng; i++)
    {
        if (s[i] > c)
            c = s[i];
    }
    for (int i = 0; i < leng; i++)
    {
        if (c == s[i])
            cout << s[i];
    }
    cout << "\n";
    return 0;
}