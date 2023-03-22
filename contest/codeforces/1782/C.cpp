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
    int n;
    string s;
    cin >> n >> s;
    vi freq(26), find;
    for (auto &ch : s) freq[ch - 'a']++;
    int ans = 2 * INF, f, same;
    for (int i = 1; i <= 26; i++) {
        if (n % i) continue;
        int targ = n / i;
        int cur = 0;
        vi ind(26);
        iota(all(ind), 0);
        sort(all(ind), [&](int x, int y) {
                 int i = freq[x], j = freq[y];
                 // if (i >= targ && j >= targ) return i > j;
                 // if (i >= targ) return false;
                 // if (j >= targ) return true;
                 return i > j;
             });
        // dbg(ind);
        for (int j = 0; j < i; j++) cur += abs(freq[ind[j]] - targ);
        for (int j = i; j < 26; j++) cur += freq[ind[j]];
        dbg(cur, i);
        if (ckmin(ans, cur / 2)) find = ind, f = targ, same = i;
    }
    vi targs(26);
    dbg(f, same);
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            if (find[j] == i) {
                targs[i] = (j >= same ? 0 : f);            
            }
        }
    }
    cout << ans << '\n';
    for (auto &ch : s) {
        char fch = ch;
        if (freq[ch - 'a'] > targs[ch - 'a']) {
            for (int i = 0; i < 26; i++) {
                if (freq[i] < targs[i]) {
                    fch = (char)(i + 'a');
                    freq[i]++;
                    freq[ch - 'a']--;
                    break;
                }
            } 
        }
        ch = fch;
    }
    cout << s << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

