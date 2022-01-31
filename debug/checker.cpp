#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using pi = pair<int, int>;
using ll = long long;
#define pb push_back
#define fi first
#define se second
#define ar array
#define sz(x) (int)(x).size()

int main(int argc, char *argv[])
{
    ifstream fin("input_file", ifstream::in);
    ifstream ans("myAnswer", ifstream::in);
    // ifstream cor("correctAnswer", ifstream::in);
    int n;
    char c;
    string s;
    fin >> n >> n >> c >> s;
    int k;
    ans >> k;
    vi ind(k);
    for (int i = 0; i < k; ++i)
        ans >> ind[i];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            if ((i + 1) % ind[j] != 0)
                s[i] = c;
        }
        if (s[i] != c)
        {
            cout << "Position " << i << " Wrong"
                 << "\n";
            return -1;
        }
    }

    return 0;
}