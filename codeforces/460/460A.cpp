#include <iostream>

using namespace std;

int main()
{
    int m, n;
    cin >> n >> m;
    int k = (int)n / (m - 1);
    int a = n % (m - 1);
    if (a == 0)
    {
        a = -1;
    }
    cout << k * m + a << "\n";

    return 0;
}