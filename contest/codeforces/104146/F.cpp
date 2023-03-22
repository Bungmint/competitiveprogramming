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
    int n, k;
    cin >> n >> k;
    string str1, str2;
    vi ans1, ans2;
    vi ind(n);
    vector<vector<vector<char>>> freq(n, vector<vector<char>>(4));
    iota(all(ind), 0);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (auto &ch : s) freq[i][(ch - '0') % 4].pb(ch);
    }
    {
        sort(all(ind), [&](int i, int j) {
                 int si = sz(freq[i][1]) + sz(freq[i][3]);
                 int sj = sz(freq[j][1]) + sz(freq[j][3]);
                 if (si != sj) return si > sj;
                 return sz(freq[i][0]) > sz(freq[j][0]);
             });
        bool has_zero = 0;
        for (int i = 0; i < k; i++) {
            ans1.pb(ind[i]);
            for (auto &ch : freq[ind[i]][1]) str1 += ch;
            for (auto &ch : freq[ind[i]][3]) str1 += ch;
            if (!has_zero && sz(freq[ind[i]][0]) && sz(str1)) {
                has_zero = 1;
                str1 += freq[ind[i]][0].front();
            }
        }
        dbg(str1);
    }
    {
        sort(all(ind), [&](int i, int j) {
                 return sz(freq[i][2]) > sz(freq[j][2]);
             });
        for (int i = 0; i < k; i++) {
            ans2.pb(ind[i]);
            for (auto &ch : freq[ind[i]][2]) str2 += ch;
        }
        dbg(str2);
    }
    if (sz(str1) == 0 && sz(str2) == 0) {
        for (int i = 0; i < k; i++) {
            cout << i + 1 << " \n"[i == k - 1];
        }
        cout << "empty" << '\n';
    } else if (sz(str1) > sz(str2)) {
        for (int i = 0; i < sz(ans1); i++) {
            cout << ans1[i] + 1 << " \n"[i == sz(ans1) - 1];
        } 
        cout << str1 << '\n';
    } else {
        for (int i = 0; i < sz(ans2); i++) {
            cout << ans2[i] + 1 << " \n"[i == sz(ans2) - 1];
        }
        cout << str2 << '\n';
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

