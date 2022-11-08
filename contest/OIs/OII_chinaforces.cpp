#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define maxn 10000010

int i, i1, j, k, k1, t, n, m, flag[10], a[maxn], b;
int nr[maxn][2][2], l, r, jl, jr, ty, x, y;
ll res;

struct min_stack {
    vector<array<int, 2>> v;
    min_stack(): v({}) {}

    void ins1(int p, int x) {
        while (!v.empty() && x <= v.back()[1]) v.pop_back();
    }

    void ins2(int p, int x) {
        v.pb({p, x});
    }
};

struct max_stack {
    vector<array<int, 2>> v;
    max_stack(): v({}) {}

    void ins1(int p, int x) {
        while (!v.empty() && x >= v.back()[1]) v.pop_back();
    }

    void ins2(int p, int x) {
        v.pb({p, x});
    }
};

min_stack s1;
max_stack s2;

ll conta(int N, vector<int> A) {
    n = N;
    for (i = 1; i <= n; i++) a[i] = A[i - 1];

    // nr[pos][</>][l/r]
    for (i = 1; i <= n; i++) {
        s1.ins1(i, a[i]); s2.ins1(i, a[i]);
        if (s1.v.empty()) nr[i][0][0] = 0;
        else nr[i][0][0] = s1.v.back()[0];
        if (s2.v.empty()) nr[i][1][0] = 0;
        else nr[i][1][0] = s2.v.back()[0];
        s1.ins2(i, a[i]); s2.ins2(i, a[i]);
    }

    s1.v.clear(); s2.v.clear();

    for (i = n; i >= 1; i--) {
        s1.ins1(i, a[i]); s2.ins1(i, a[i]);
        if (s1.v.empty()) nr[i][0][1] = n + 1;
        else nr[i][0][1] = s1.v.back()[0];
        if (s2.v.empty()) nr[i][1][1] = n + 1;
        else nr[i][1][1] = s2.v.back()[0];
        s1.ins2(i, a[i]); s2.ins2(i, a[i]);
    }

    for (i = 1; i <= n; i++) {
        l = nr[i][1][0] + 1; r = nr[i][1][1] - 1;
        jl = i; jr = i;
        while (jl >= l && jr <= r) {
            jl = nr[jl][0][0]; jr = nr[jr][0][1];
        }
        if (jl < l) ty = 0;
        else ty = 1;

        if (ty == 0) {
            jl = nr[i][0][0];
            while (jl >= l) {
                x = max(l - 1, nr[jl][0][0]); y = min(r + 1, nr[jl][0][1]);
                res += ((ll)(jl - x) * (y - i));
                jl = nr[jl][0][0];
            }
        } else {
            jr = i;
            while (jr <= r) {
                x = max(l - 1, nr[jr][0][0]); y = min(r + 1, nr[jr][0][1]);
                res += ((ll)(x - l + 1) * (y - jr));
                jr = nr[jr][0][1];
            }
        }
    }

    return res;
}