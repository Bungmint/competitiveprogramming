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

/**
 * Description: Sort suffixes. The first element of SA is sz(S)
 * Source: Benq
 * Verification:
 * Time complexity: O(nlogn)
 */

// #include "miscellaneous/template.h"

struct SuffixArray {
    string s; 
    int n;
    vi sa, c;
    SuffixArray(const string &_s) : s(_s)  {
        s += (char)('a' - 1);
        n = sz(s);
        generate_sa();
    }
    void count_sort_zero() {
        vi cnt(27), pos(27);
        for (int i = 0; i < n; i++) cnt[s[i] + 1 - 'a']++;
        for (int i = 1; i < 27; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        for (int i = 0; i < n; i++) {
            sa[pos[s[i] + 1 - 'a']++] = i;
        }
        c[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            c[sa[i]] = c[sa[i - 1]];
            if (s[sa[i]] != s[sa[i - 1]]) c[sa[i]]++;
        }
    }
    void count_sort(int k) {
        vi cnt(n), pos(n), new_sa(n), new_c(n);
        for (int i = 0; i < n; i++) cnt[c[i]]++;
        for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        for (int i = 0; i < n; i++) {
            new_sa[pos[c[sa[i]]]++] = sa[i];
        }
        swap(sa, new_sa);
        for (int i = 1; i < n; i++) {
            new_c[sa[i]] = new_c[sa[i - 1]];
            if (c[sa[i]] != c[sa[i - 1]] || 
            c[(sa[i] + (1 << k)) % n] != c[(sa[i - 1] + (1 << k)) % n]) {
                new_c[sa[i]]++;
            }
        }
        swap(c, new_c);
    }
    void generate_sa() {
        int k = 0;
        sa.resize(n); c.resize(n);
        count_sort_zero();
        while ((1 << k) < n) {
            for (auto &x : sa) {
                x -= (1 << k);
                if (x < 0) x += n;
            }
            count_sort(k++);
        }
    }
};




void solve() {
	string t; cin >> t;
	SuffixArray sa(t);
	int n = sz(t);
	int q; cin >> q;
	for (int i = 0; i < q; i++) {
		string s;
		cin >> s;
		int lo = 1, hi = n;
		bool ans = 0;
		while (lo <= hi) {
			int mid = (lo + hi) / 2;
			int ind = sa.sa[mid];
			int len = min(n - ind, sz(s));
			string tt = t.substr(ind, len);
			if (tt == s) { ans = 1; break; }
			else if (tt < s) lo = mid + 1;
			else hi = mid - 1;
		}
		cout << (ans ? "Yes" : "No") << '\n';
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
