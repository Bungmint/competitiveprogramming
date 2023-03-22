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
    int t, vs;
    ll k;
    cin >> t >> k;
    t--;
    vector<vl> a(4, vl(4));
    for (auto &v : a) for (auto &e : v) cin >> e;
    vl ps(4), rel_score(4), score(4);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) continue;
            if (a[i][j] == -1) {
                vs = j;
                continue;
            }
            rel_score[i] += a[i][j]; 
            score[i] += a[i][j];
            if (a[j][i] != -1) {
                rel_score[i] -= a[j][i];
                if (a[i][j] == a[j][i]) ps[i]++;
                if (a[i][j] > a[j][i]) ps[i] += 3;
            }
        }
    }
    ll ans = k + 1;
    vl interest = {0, k};
    interest.pb(a[vs][t]);
    for (int i = 0; i < 4; i++) {
        if (i == t) {
            continue; 
        }
        ll tmp = score[i] - score[t];
        if (tmp >= 0 && tmp <= k) interest.pb(tmp);
        if (i == vs) {
            ll tmp = (rel_score[vs] - rel_score[t]);
            if (tmp >= 0 && tmp <= k * 2) {
                interest.pb(tmp / 2), interest.pb(tmp / 2 + 1); 
            }
        } else {
            ll tmp = (rel_score[i] - rel_score[t]);
            if (tmp >= 0 && tmp <= k) interest.pb(tmp);
            tmp = (rel_score[vs] - rel_score[i]);
            if (tmp >= 0 && tmp <= k) interest.pb(tmp);
        }
    }
    sort(all(interest)), interest.resize(unique(all(interest)) - interest.begin());
    while (interest.back() > k) interest.pop_back();
    auto calc_rank = [&](ll e) {
        vl ps_copy = ps;
        vl rs = rel_score, s = score;  
        vi ind = {0, 1, 2, 3};
        if (e > a[vs][t]) ps_copy[t] += 3; 
        if (e == a[vs][t]) ps_copy[t]++, ps_copy[vs]++;
        if (e < a[vs][t]) ps_copy[vs] += 3;
        rs[t] += e;
        rs[vs] -= e;
        s[t] += e;
        sort(all(ind), [&](int i, int j) {
                if (ps_copy[i] != ps_copy[j]) return ps_copy[i] > ps_copy[j];
                if (rs[i] != rs[j]) return rs[i] > rs[j];
                if (s[i] != s[j]) return s[i] > s[j];
                return i < j;
             });
        if (ind[0] == t || ind[1] == t) {
            ckmin(ans, e);
        }
    };
    for (auto &e : interest) {
        for (ll mid = e; mid <= min(k, e + 1); mid++) {
            calc_rank(mid);
        }
    }
    cout << (ans == k + 1 ? -1 : ans) << '\n';
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

