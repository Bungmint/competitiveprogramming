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

using Point = pii;
int freq[1 << 18];
map<char, int> letter = {{'L', 0}, {'R', 1}, {'S', 2}, {'A', 3}};
vector<Point> locks;

int sgn(int x) {
    return (x > 0) - (x < 0);
}
int cross(Point u, Point v) {
    return u.fi * v.se - u.se * v.fi;
}
int dot(Point u, Point v) {
    // dbg(u, v);
    return u.fi * v.fi + u.se * v.se;
}
int count_pattern(const string& s, int id, int mask) {
    // dbg(mask);
    if (id == sz(s)) return freq[mask];
    int res = 0;
    if (letter.count(s[id])) {
        res = count_pattern(s, id + 1, mask ^ (letter[s[id]] << (2 * id)));
    } else {
        for (int i = 0; i < 4; i++) {
            res += count_pattern(s, id + 1, mask ^ (i << (2 * id)));
        }
    }
    return res;
}

Point operator-(const Point& lhs, const Point& rhs) {
    return {lhs.fi - rhs.fi, lhs.se - rhs.se};
}

char calc(int i, int j, int k) {
    int left_right = sgn(cross(locks[j] - locks[i], locks[k] - locks[j]));
    if (left_right == 1) return 'L';
    if (left_right == -1) return 'R';
    // dbg(locks[j] - locks[i], locks[k] - locks[j]);
    // dbg(dot(locks[j] - locks[i], locks[k] - locks[j]));
    return (sgn(dot(locks[j] - locks[i], locks[k] - locks[j])) == 1 ? 'S' : 'A');
}
int abs(const Point& p) {
    return p.fi * p.fi + p.se * p.se;                
}

void solve() {
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
        locks.pb({i, j});
    }	
    vi ind(9);
    iota(all(ind), 0);
    dbg(calc(3, 4, 5));
    do {
        int mask = 0;
        bool ok = 1;
        for (int i = 0; i < 9; i++) {
            {
                for (int k = i + 2; k < 9; k++) {
                    ok &= (calc(ind[i], ind[i + 1], ind[k]) != 'A' || abs(ind[i + 1] - ind[i]) < abs(ind[k] - ind[i + 1]));
                }
            }
        }
        if (!ok) continue;
        for (int i = 0; i < 7; i++) {
            int bit = letter[calc(ind[i], ind[i + 1], ind[i + 2])];
            mask += bit << (2 * i);
        } 
        freq[mask]++;
    } while (next_permutation(all(ind)));
    string s;
    cin >> s;
    cout << count_pattern(s, 0, 0) << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

