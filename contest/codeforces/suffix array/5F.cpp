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
 * Description: Sort suffixes. The first element of SA is sz(S),
    * isa is the inverse of sa, and lcp stores
    * the longest common prefix of two consecutive elements of sa
 * Source: Benq
 * Verification:
 * Time complexity: O(nlogn)
 */

/**
 * Description: Data structure that supports range idempotent queries on a static array
 * Source: Own
 * Verification:
 * Time Complexity: O(nlogn) build, O(1) query
 */

template <typename T>
struct SparseTable{
	vector<vector<T>> spar;
	inline T merge(const T& a, const T& b) { // change this
		return min(a, b);
	} 
	SparseTable() {}
	SparseTable(const vector<T>& a) {
		int lg = 32 - __builtin_clz(sz(a));
		spar.assign(lg, vi(sz(a), 0));
		for (int i = 0; i < sz(a); ++i) spar[0][i] = a[i];
		for (int j = 1; j < lg; ++j) 
			for (int i = 0; i + (1 << j) <= sz(a); ++i)
				spar[j][i] = merge(spar[j - 1][i], spar[j - 1][i + (1 << (j - 1))]);
	}
	SparseTable(T a[], int n) {
		int lg = 32 - __builtin_clz(n);
		spar.assign(lg, vi(n, 0));
		for (int i = 0; i < n; ++i) spar[0][i] = a[i];
		for (int j = 1; j < lg; ++j) 
			for (int i = 0; i + (1 << j) <= n; ++i)
				spar[j][i] = merge(spar[j - 1][i], spar[j - 1][i + (1 << (j - 1))]);
	}
	T query(int a, int b) {
		assert(a <= b);
		int dif = 31 - __builtin_clz(b - a + 1);
		return merge(spar[dif][a], spar[dif][b - (1 << dif) + 1]);
	}
};

struct SuffixArray {
    string s; 
    int n;
    vi sa, isa, lcp;
    SparseTable<int> rmq;
    SuffixArray(const string &_s) : s(_s) {
        s += (char)(0);
        n = sz(s);
        generate_sa();
        generate_lcp();
    }
    void count_sort_zero() {
        vi cnt(128), pos(128);
        for (int i = 0; i < n; i++) cnt[s[i]]++;
        for (int i = 1; i < 128; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        for (int i = 0; i < n; i++) {
            sa[pos[s[i]]++] = i;
        }
        isa[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            isa[sa[i]] = isa[sa[i - 1]];
            if (s[sa[i]] != s[sa[i - 1]]) isa[sa[i]]++;
        }
    }
    void count_sort(int k) {
        vi cnt(n), pos(n), new_sa(n), new_isa(n);
        for (int i = 0; i < n; i++) cnt[isa[i]]++;
        for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        for (int i = 0; i < n; i++) {
            new_sa[pos[isa[sa[i]]]++] = sa[i];
        }
        swap(sa, new_sa);
        for (int i = 1; i < n; i++) {
            new_isa[sa[i]] = new_isa[sa[i - 1]];
            if (isa[sa[i]] != isa[sa[i - 1]] || 
            isa[(sa[i] + (1 << k)) % n] != isa[(sa[i - 1] + (1 << k)) % n]) {
                new_isa[sa[i]]++;
            }
        }
        swap(isa, new_isa);
    }
    void generate_sa() {
        int k = 0;
        sa.resize(n); isa.resize(n);
        count_sort_zero();
        while ((1 << k) < n) {
            for (auto &x : sa) {
                x -= (1 << k);
                if (x < 0) x += n;
            }
            count_sort(k++);
        }
    }
    void generate_lcp() {
        lcp.resize(n - 1);
        int k = 0;
        for (int i = 0; i < n - 1; i++) {
            int pi = isa[i];
            int j = sa[pi - 1];
            while (s[i + k] == s[j + k]) k++;
            lcp[pi - 1] = k;
            if (k) k--;
        }
        rmq = SparseTable<int>(lcp);
    }
    int get_lcp(int a, int b) {
        if (a == b) return sz(s) - a;
        int l = isa[a], r = isa[b];
		if (l > r) swap(l, r);
        return rmq.query(l, r - 1);
    }
};


void solve() {
	string s;
	cin >> s;
	SuffixArray sa(s);
	reverse(all(s));
	SuffixArray rev_sa(s);
	int n = sz(s), ans = 1;
	for (int L = 1; L < n; L++) {
		for (int i = 0, j = L; j < n; i += L, j += L) {
			int a = sa.get_lcp(i, j);
			int b = rev_sa.get_lcp(n - i - L, n - i);
			dbg(a, b, i);
			ckmax(ans, (a + b)/L + 1);
		}
	}
	cout << ans << '\n';
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
