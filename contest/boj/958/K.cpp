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




/**
 * Description: Mo's Trick using the Hilbert curve
 * Source: 
 	* https://cp-algorithms.com/data_structures/sqrt_decomposition.html#mos-algorithm
	* https://en.wikipedia.org/wiki/Hilbert_curve#Applications_and_mapping_algorithms
 * Verification: Various
 * Time complexity: O(q\sqrt{n})
 */

ll hilbertorder(int x, int y) {
	constexpr int LOGN = 20, MAXN = 1 << LOGN;
	ll d = 0;
	for (int s = 1 << (LOGN - 1); s; s >>= 1) {
		bool rx = x & s, ry = y & s;
		d = d << 2 | (rx * 3 ^ static_cast<int>(ry));
		if (!ry) {
			if (rx) x = MAXN - x, y = MAXN - y;
			swap(x, y);
		}
	}
	return d;
}

struct Query {
    int l, r, idx;
    ll k;
    ll ord;
	inline void calcOrder() {
		ord = hilbertorder(l, r);
	}
};
inline bool operator<(const Query &a, const Query &b) {
	return a.ord < b.ord;
}

struct SqrtPURQ {
    constexpr static int B = 710;
    ll cnt[500100], block_cnt[B];
    SqrtPURQ() { memset(cnt, 0, sizeof(cnt)); memset(block_cnt, 0, sizeof(block_cnt)); }
    void upd(int i, ll v) {
        cnt[i] += v;
        block_cnt[i / B] += v;
    }
    int query(ll x) {
        for (int i = 0; i < B; i++) {
            if (block_cnt[i] >= x) {
                for (int j = 0; j < B; j++) {
                    if (cnt[i * B + j] >= x) {
                        return i * B + j;
                    }
                    x -= cnt[i * B + j];
                }
            } else {
                x -= block_cnt[i];
            }
        }
        return -1;
    }
};

vector<map<int, int>> to_left;
vector<map<int, int>> to_right;
vector<vpi> to_to_left, to_to_right;
SqrtPURQ seg;

void remove_left(int idx, int right_end) {
    int gg = -1, pre = -1;
    dbg(idx, right_end);
    for (auto &[g, pos] : to_to_right[idx]) {
        if (pos > right_end) {
            break;
        }
        if (gg != -1) {
            seg.upd(gg, -(pos - pre));
        } 
        gg = g;
        pre = pos;
    }
    seg.upd(gg, -(right_end - pre + 1));
}
void remove_right(int idx, int left_end) {
    int gg = -1, pre = -1;
    for (auto &[g, pos] : to_to_left[idx]) {
        if (pos < left_end) {
            break;
        }
        if (gg != -1) {
            seg.upd(gg, -(pre - pos));
        } 
        gg = g;
        pre = pos;
    }
    seg.upd(gg, -(pre - left_end + 1));

}
void add_left(int idx, int right_end) {
    int gg = -1, pre = -1;
    for (auto &[g, pos] : to_to_right[idx]) {
        if (pos > right_end) {
            break;
        }
        if (gg != -1) {
            seg.upd(gg, pos - pre);
        } 
        gg = g;
        pre = pos;
    }
    seg.upd(gg, right_end - pre + 1);
}
void add_right(int idx, int left_end) {
    int gg = -1, pre = -1;
    for (auto &[g, pos] : to_to_left[idx]) {
        if (pos < left_end) {
            break;
        }
        if (gg != -1) {
            // dbg(idx, gg, pre - pos);
            seg.upd(gg, pre - pos);
        } 
        gg = g;
        pre = pos;
    }
    // dbg(idx, gg, pre - left_end + 1);
    seg.upd(gg, pre - left_end + 1);
}
ll get_answer(ll k) {
    return seg.query(k);
}

vl mo(vector<Query> queries) {
   	vl answers(queries.size());
    for (auto &e : queries) e.calcOrder();
    sort(queries.begin(), queries.end());

    int cur_l = 0;
    int cur_r = -1;
    for (Query q : queries) {
        dbg(cur_l, cur_r, q.l, q.r);
        while (cur_l > q.l) { cur_l--; add_left(cur_l, cur_r); }
        while (cur_r < q.r) { cur_r++; add_right(cur_r, cur_l); }
        while (cur_l < q.l) { remove_left(cur_l, cur_r); cur_l++; }
        while (cur_r > q.r) { remove_right(cur_r, cur_l); cur_r--; }
        answers[q.idx] = get_answer(q.k);
    }
    return answers;
}

void solve() {
    int n, q;
    cin >> n;
    to_left.resize(n), to_right.resize(n);    
    to_to_left.resize(n), to_to_right.resize(n);
    vi a(n);
    for (auto &e : a) cin >> e;
    cin >> q;
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        ll k;
        cin >> l >> r >> k;
        queries[i].l = l - 1;
        queries[i].r = r - 1;
        queries[i].k = k;
        queries[i].idx = i;
    }

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            to_left[i][a[i]] = i;
        } else {
            to_left[i][a[i]] = i;
            for (auto &[g, pos] : to_left[i - 1]) {
                int gg = gcd(g, a[i]); 
                if (!to_left[i].count(gg)) to_left[i][gg] = pos;
                ckmax(to_left[i][gg], pos);
            }
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        to_right[i][a[i]] = i;
        if (i == n - 1) {
            continue;
        }
        for (auto &[g, pos] : to_right[i + 1]) {
            int gg = gcd(g, a[i]);
            if (!to_right[i].count(gg)) to_right[i][gg] = pos;
            ckmin(to_right[i][gg], pos);
        }
    }
    for (int i = 0; i < n; i++) {
        for (auto &[g, pos] : to_left[i]) to_to_left[i].pb({g, pos});
        for (auto &[g, pos] : to_right[i]) to_to_right[i].pb({g, pos});
        sort(all(to_to_left[i]), [&](auto a, auto b) {
                 return a.se > b.se;
             });
        sort(all(to_to_right[i]), [&](auto a, auto b) {
                 return a.se < b.se;
             });
    }
    vl ans = mo(queries);
    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
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

