#include <bits/stdc++.h>

using namespace std;
const int T = 2019;
int occurrance[T] = {0};
int arr[200001] = {0};
int c_i(char c)
{
    return c - '0';
}

int mod_power(int num, int exp)
{
    if (exp == 0)
        return 1;
    if (exp == 1)
        return num;
    int x = mod_power(num, exp / 2);
    if (exp % 2 == 0)
    {
        return x * x % T;
    }
    else
    {
        return ((x * x % T) * num) % T;
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    string s;
    cin >> s;
    int leng = s.length();
    long long counter = 0;
    occurrance[0] += 1;
    for (int i = leng - 1; i >= 0; i--)
    {
        int x = mod_power(10, leng - i - 1);
        arr[i] = (arr[i + 1] + x * c_i(s[i])) % T;
        occurrance[arr[i]] += 1;
    }
    for (auto x : occurrance)
    {

        counter += x * (x - 1) / 2;
    }
    cout << counter << "\n";
    return 0;
}