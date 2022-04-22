#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;
using vi = vector<int>;
using vvi = vector<vi>;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, b) FOR(i, 0, b)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); i--)
#define R0F(i, b) ROF(i, 0, b)
#define sz(x) (int)(x).size()


void dbg_out() {
	cerr << endl;
}
template<typename T, typename...Us>
void dbg_out(T&& a, Us&&... b) {
	cerr << " " << forward<T>(a);
	(int[]){(cerr << " " << forward<Us>(b), 0)...};
	cerr << endl;
}

#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

const int MOD = 1e9 + 7;

void add_(int &a, int b) {
	(a += b) %= MOD;
}


class SubmultiplesOfN {
	public:
		int count(string B, int N) {
			vi num(sz(B));
			F0R(i, sz(B)) num[i] = B[i] - '0';
			vvi earliest(sz(B), vi(10, -1));
			R0F(i, sz(B)) {
				F0R(j, i + 1) {
					earliest[j][num[i]] = i;
				}
			}
			vvi dp(sz(B), vi(N));
			FOR(i, 1, 10) {
				if (earliest[0][i] >= 0) dp[earliest[0][i]][i % N] = 1;
			}
			F0R(i, sz(B) - 1) {
				F0R(m, N) {
					F0R(d, 10) {
						if (earliest[i + 1][d] == -1) continue;
						int nxt = 10 * m + d; nxt %= N;
						int go = earliest[i + 1][d];
						dp[go][nxt] += dp[i][m];
						dp[go][nxt] %= MOD;
					}
				}
			}
			dbg();
			int ans = 0;
			F0R(i, sz(B)) {
				add_(ans, dp[i][0]);
			}
			return ans;
		}
};

int main() {
	SubmultiplesOfN obj;
	string s; int n;
	cin >> s >> n;
	dbg(s, n);
	cout << obj.count(s, n) << "\n";
}
