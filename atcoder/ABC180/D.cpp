#include <bits/stdc++.h>

using namespace std;

__int128 read()
{
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(__int128 x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
bool cmp(__int128 x, __int128 y) { return x > y; }

int main()
{
    __int128_t x, y, a, b;
    x = read();
    y = read();
    a = read();
    b = read();
    __int128_t xp = 0;
    while ((a - 1) * x < b && a * x < y)
    {
        x = a * x;
        xp++;
    }
    __int128_t k = (y - x - 1) / b;
    xp += k;
    print(xp);
    cout << "\n";
}