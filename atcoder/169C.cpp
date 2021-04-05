#include <bits/stdc++.h>

using namespace std;

long long c_i(char x)
{
    return x - '0';
}

bool double_abs(double x, double y)
{
    if (abs(x - y) <= 1 - 1e-9)
        return true;
    return false;
}

int main()
{
    long long a;
    float b;
    cin >> a >> b;
    string e = to_string(b);
    long long d = c_i(e[0]) * 100 + c_i(e[2]) * 10 + c_i(e[3]);
    long long c = (a * d) / 100;
    cout << c << endl;
    return 0;
}