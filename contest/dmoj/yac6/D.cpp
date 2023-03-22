// Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

#pragma region TEMPLATE

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
using ld = long double;
template <typename T, size_t SZ>
using ar = array<T, SZ>;
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

#define all(v) (v).begin(), (v).end()
#define pb push_back
#define eb emplace_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound

constexpr int INF = 1e9;
constexpr ll LINF = 1e18;
const ld PI = acos((ld)-1.0);
constexpr int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
constexpr bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
constexpr bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }
ll cdiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // divide a by b rounded down

#ifdef LOCAL
#include "miscellaneous/debug.h"
#else
#define dbg(...) 42
#endif

inline namespace RecursiveLambda {
	template <typename Fun>
	struct y_combinator_result {
		Fun fun_;
		template <typename T>
		explicit constexpr y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}
		template <typename... Args>
		constexpr decltype(auto) operator()(Args &&...args) const {
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun) {
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

#pragma endregion TEMPLATE

vi sg;
int N, M;
int xum;

// Definitely not intended? Local calculation O(MAXS ^ 4) took 13s
void precalc() {
    vi t = {0, 0,
1,
2,
2,
7,
3,
5,
4,
5,
10,
9,
9,
15,
5,
12,
14,
17,
15,
17,
17,
23,
24,
27,
22,
34,
18,
28,
41,
29,
21,
34,
33,
41,
26,
55,
30,
42,
35,
39,
34,
56,
65,
39,
41,
47,
45,
43,
40,
40,
29,
44,
58,
56,
52,
57,
55,
54,
55,
48,
61,
60,
60,
58,
44,
67,
67,
64,
64,
37,
66,
64,
74,
70,
72,
47,
66,
75,
74,
73,
90,
81,
79,
80,
78,
81,
87,
95,
95,
83,
124,
92,
93,
86,
67,
91,
97,
88,
97,
100,
103
};
    sg = t;
}

void solve() {
    cin >> N >> M;	
    for (int i = 0; i < N; i++) {
        int s;
        cin >> s;
        xum ^= sg[s];
    }
    for (int i = 1; i <= M; i++) {
        if ((xum ^ sg[i]) == 0) {
            cout << i << '\n';
            return;
        }
    }
    cout << -1 << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
    precalc();
    solve();
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

