#include <bits/stdc++.h>
#define SIZE 1000001
using namespace std;
using ll = long long;
ll a[SIZE];
ll afs[SIZE];

void precalculate()
{
    for (int i = 2; i < SIZE; i++)
    {
        a[i] = 1;
    }

    for (int i = 2; i < SIZE; i++)
    {
        int j = 2;
        int n;
        while ((n = i * j) < SIZE)
        {
            a[n] += i;
            j++;
        }
    }

    afs[0] = 0;
    afs[1] = 0;

    for (int i = 2; i < SIZE; i++)
    {
        afs[i] = a[i] + afs[i - 1];
    }
}

int main()
{
    precalculate();
    ios_base::sync_with_stdio(0),
        cin.tie(0), cout.tie(0);
    int t;
    cin >> t;

    while (t--)
    {
        int x;
        cin >> x;
        cout << afs[x] << "\n";
    }
    return 0;
}