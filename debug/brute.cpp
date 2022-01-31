#include <bits/stdc++.h>
using namespace std;

bool good(int l, int r, string &s)
{
    stack<int> st;
    for (int i = l; i <= r; ++i)
    {
        if (s[i] == '(')
        {
            st.push(i);
        }
        else
        {
            if (st.size() == 0)
                return false;
            st.pop();
        }
    }
    return st.size() == 0;
}

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    string s = "";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < a[i]; ++j)
        {
            if (i & 1)
                s += ')';
            else
                s += '(';
        }
    }
    int ans = 0;
    for (int i = 0; i < (s).length(); ++i)
    {
        for (int j = i; j < s.length(); ++j)
        {
            ans += !!(good(i, j, s));
        }
    }
    cout << ans << "\n";
}
