#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using ll = long long;
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int a, int b)
{
    return a + rand() % (b - a + 1);
}
int main(int argc, char *argv[])
{
    int seed = atoi(argv[1]);
    srand(seed);
}