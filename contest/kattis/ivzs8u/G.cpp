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

void solve() {
    string s, t;
    cin >> s >> t;
    int n = sz(s), m = sz(t);
    int a = count(all(s), '+'), b = count(all(s), '-');
    if (a == 0 || b == 0) {
        if (a == 0 && b == 0) {
            cout << (s == t ? "<any> <any>" : "corrupted") << '\n';
        }else if (a == 0) {
            int j = (m - n + b) / b;
            if (j < 0 || j * b != m - n + b) {
                cout << "corrupted" << '\n';
            }else{
                bool foundb = 0;
                bool ok = 1;
                int ptr = 0, bst = 0;
                for (int k = 0; k < n; k++) {
                    if (s[k] == '-') {
                        if (!foundb) {
                            foundb = 1;
                            bst = ptr;
                        }else{
                            for (int x = 0; x < j; x++) {
                                ok &= t[ptr + x] == t[bst + x];
                            }
                        }
                        ptr += j;
                    }else{
                        ok &= s[k] == t[ptr++];
                    }
                }
                if (ok) {
                    string aa = "<any>", bb;
                    for (int x = 0; x < j; x++) {
                        bb += t[bst + x];
                    }
                    if (bb == "") bb = "<empty>";
                    cout << aa << ' ' << bb << '\n';
                }else{
                    cout << "corrupted" << '\n';
                }
            }
        }else{
            int j = (m - n + a) / a;
            if (j < 0 || j * a != m - n + a) {
                cout << "corrupted" << '\n';
            }else{
                bool foundb = 0;
                bool ok = 1;
                int ptr = 0, bst = 0;
                for (int k = 0; k < n; k++) {
                    if (s[k] == '+') {
                        if (!foundb) {
                            foundb = 1;
                            bst = ptr;
                        }else{
                            for (int x = 0; x < j; x++) {
                                ok &= t[ptr + x] == t[bst + x];
                            }
                        }
                        ptr += j;
                    }else{
                        ok &= s[k] == t[ptr++];
                    }
                }
                if (ok) {
                    string aa, bb = "<any>";
                    for (int x = 0; x < j; x++) {
                        aa += t[bst + x];
                    }
                    if (aa == "") aa = "<empty>";
                    cout << aa << ' ' << bb << '\n';
                }else{
                    cout << "corrupted" << '\n';
                }
            } 
        }
        return;
    }
    int cnt = 0;
    for (int i = 0; i <= m; i++) {
        if (a * i > m - n + a + b) break;
        if ((m - n + a + b - a * i) % b) continue;
        int j = (m - n + a + b - a * i) / b;
        bool founda = 0, foundb = 0;
        bool ok = 1;
        int ast = 0, bst = 0;
        int ptr = 0;
        for (int k = 0; k < n; k++) {
            if (s[k] == '+') {
                if (!founda) {
                    founda = 1;
                    ast = ptr;
                }else{
                    for (int x = 0; x < i; x++) {
                        if (t[ptr + x] != t[ast + x]) ok = 0;
                    }
                }
                ptr += i; 
            }else if (s[k] == '-') {
                if (!foundb) {
                    foundb = 1;
                    bst = ptr;
                }else{
                    for (int x = 0; x < j; x++) {
                        if (t[ptr + x] != t[bst + x]) ok = 0;
                    }
                }
                ptr += j; 
            }else{
                ok &= t[ptr++] == s[k];    
            }
        }
        if (ok) {
            cnt++;
            string aa, bb;
            for (int x = 0; x < i; x++) aa += t[ast + x];
            for (int x = 0; x < j; x++) bb += t[bst + x];
            if (aa == "") aa = "<empty>";
            if (bb == "") bb = "<empty>";
            cout << aa << ' ' << bb << '\n';
        }
    }
    if (!cnt) {
        cout << "corrupted" << '\n';
    }
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

