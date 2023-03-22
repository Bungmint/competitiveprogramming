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

constexpr ld EPS = 1e-8;
constexpr int MAXN = 211;
ld dp[MAXN][MAXN];
ll k[MAXN], prefk[MAXN], prefik[MAXN], prefiik[MAXN];
int N, M;

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> k[i];
        prefk[i] = prefk[i - 1] + k[i];
        prefik[i] = prefik[i - 1] + i * k[i];
        prefiik[i] = prefiik[i - 1] + i * i * k[i];
    }
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            dp[i][j] = LINF;
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            for (int x = 0; x < i; x++) {
                if (dp[x][j - 1] > LINF / 2.0) continue;
                ll sk = prefk[i] - prefk[x];
                ll sik = prefik[i] - prefik[x];
                ll siik = prefiik[i] - prefiik[x];
                if (sk == 0) {
                    if (dp[i][j] > dp[x][j - 1] + EPS) {
                        dp[i][j] = dp[x][j - 1];
                    } 
                }else{
                    ld mi = siik - (ld)(sik) / (ld)(sk) * (ld)(sik);
                    if (dp[i][j] > dp[x][j - 1] + mi + EPS) {
                        dp[i][j] = dp[x][j - 1] + mi;
                    }  
                }
            }
        }
    }
    cout << fixed << setprecision(20) << '\n';
    cout << dp[N][M] << '\n';
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

