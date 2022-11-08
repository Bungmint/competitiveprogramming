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
 * Description: A fully persistent data structure that supports range updates/queries
 * Source: Benq
 * Verification:
 * Time Complexity: O(log n) time per update/query, O(log n) memory per query
 */

template <typename T, int SZ>
struct PST {
    struct Node {
        T val;
        int c[2];
        Node() {
            val = T();
            c[0] = c[1] = 0;
        }
    };
    static const int LIM = 6e6;
    Node d[LIM];
    int nxt = 0;
    int copy(int t) { d[nxt] = d[t]; return nxt++; }
    T comb(const T& a, const T& b) { return a + b; }
    void pull(int c) { d[c].val = comb(d[d[c].c[0]].val, d[d[c].c[1]].val); }
    T query(int lo, int hi, int t, int l, int r) {
        if (lo >= r || hi <= l) return T();
        if (lo <= l && r <= hi) return d[t].val;
        int m = (l + r) / 2;
        T lef = query(lo, hi, d[t].c[0], l, m);
        T rig = query(lo, hi, d[t].c[1], m, r);
        return comb(lef, rig);
    }
    int upd(int i, const T& v, int t, int l, int r) {
        int x = copy(t);
        if (r - l == 1) {
            d[x].val = v;
            return x;
        }
        int m = (l + r) / 2;
        if (i < m) {
            d[x].c[0] = upd(i, v, d[x].c[0], l, m);
        }else{
            d[x].c[1] = upd(i, v, d[x].c[1], m, r);
        }
        pull(x);
        return x;
    }
    int build(const vector<T>& a, int l, int r) {
        int c = nxt++;
        if (r - l == 1) {
            if (l < sz(a)) d[c].val = a[l];
            return c;
        }
        int m = (l + r) / 2;
        d[c].c[0] = build(a, l, m);
        d[c].c[1] = build(a, m, r);
        pull(c);
        return c;
    }
    vi rts;
    int update_time(int ti, int i, const T& v) {
        rts.pb(upd(i, v, rts[ti], 0, SZ));
		return sz(rts) - 1;
    }
    void build(const vector<T>& a) {
        rts.pb(build(a, 0, SZ));
    }
    T query_time(int ti, int lo, int hi) {
        return query(lo, hi, rts[ti], 0, SZ);
    }
	int copy_root(int ti) {
		rts.pb(copy(rts[ti]));
		return sz(rts) - 1;
	}
};
PST<ll, 1 << 18> pst;

void solve() {
	int N, Q;
	cin >> N >> Q;
	vl a(N);
	for (int i = 0; i < N; i++) cin >> a[i];
	pst.build(a);
	vi ind{0};
	for (int i = 0; i < Q; i++) {
		dbg(ind);
		int op; cin >> op;
		if (op == 1) {
			int k, id, x;
			cin >> k >> id >> x;
			k--, id--;
			ind[k] = pst.update_time(ind[k], id, x);
		}else if (op == 2) {
			int k, l, r;
			cin >> k >> l >> r;
			k--, l--, r--;
			cout << pst.query_time(ind[k], l, r + 1) << '\n';
		}else {
			int k;
			cin >> k;
			k--;
			ind.pb(pst.copy_root(ind[k]));
		}
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
