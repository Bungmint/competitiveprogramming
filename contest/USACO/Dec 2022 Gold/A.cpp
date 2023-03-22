#include <bits/stdc++.h>
using namespace std;

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


constexpr int MAXN = 2011;
int P[MAXN], C[MAXN], X[MAXN];
int id[MAXN];
int dp[2][MAXN];
int max_val[2][MAXN][MAXN];
int N, A, B;

// O(NA) solution
void solve() {
    cin >> N >> A >> B;
    for (int i = 1; i <= N; i++) cin >> P[i] >> C[i] >> X[i];
    iota(id, id + N, 1);
    sort(id, id + N, [&](int i, int j){ return X[i] < X[j]; });
    int ans = 0;
    for (int iter = 0; iter < 2; iter++, reverse(id, id + N)) {
        for (int ii = 0; ii < N; ii++) {
            int i = id[ii];
            if (iter == 0) {
                for (int j = B; j >= 0; j--) {
                    max_val[iter][i][j] = dp[iter][j];
                }
                for (int j = B; j >= X[i] * C[i]; j--) {
                    ckmax(dp[iter][j], P[i] + dp[iter][j - X[i] * C[i]]); 
                } 
            }else{
                for (int j = A; j >= 0; j--) {
                    max_val[iter][i][j] = dp[iter][j];
                }
                for (int j = A; j >= C[i]; j--) {
                    ckmax(dp[iter][j], P[i] + dp[iter][j - C[i]]);
                }
            }
        } 
    }
    for (int i = 1; i <= N; i++) {
        ckmax(ans, max_val[0][i][B] + max_val[1][i][A]);
        for (int j = 0; j <= min(C[i], B / X[i]); j++) {
            if (A < C[i] - j) continue;
            ckmax(ans, P[i] + max_val[0][i][B - j * X[i]] + max_val[1][i][A - (C[i] - j)]);
        }
    }
    cout << ans << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    solve();
}

