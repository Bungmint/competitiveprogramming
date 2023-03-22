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
constexpr ld EPS = 1e-9;
int h[MAXN];
int N, Q;

// O(N^2 * Q) stack solution
void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> h[i];
    cin >> Q;
    for (int iter = 0; iter < Q; iter++) {
        int id, x;
        cin >> id >> x;
        h[id] += x;
        ll ans = 0;
        for (int i = 1; i <= N; i++) {
            ld slope = -LINF;
            for (int j = i + 1; j <= N; j++) {
                ld cur = (ld)(h[j] - h[i]) / (j - i); 
                if (cur + EPS < slope) {
                    continue;
                }
                ans++;
                slope = cur;
            } 
        } 
        cout << ans << '\n';
    } 
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    solve();
}

