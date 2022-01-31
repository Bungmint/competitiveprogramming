// Problem: C - Digit Sum Minimization
// Contest: AtCoder - AtCoder Regular Contest 130
// URL: https://atcoder.jp/contests/arc130/tasks/arc130_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2021 Youngmin Park. All rights reserved.
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
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

#define all(v) (v).begin(), (v).end()
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define REP(a) F0R(_, a)

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v)
{
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}
void dbg_out()
{
    cerr << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

struct chash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
    size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}



void solve()
{
	string a, b;
	cin >> a >> b;
	int minLen = min(sz(a), sz(b)), maxLen = max(sz(a), sz(b));
	vi digA(10), digB(10),dA, dB;
	F0R(i, sz(a)){
		digA[a[i]-'0']++;
	}
	F0R(i, sz(b)){
		digB[b[i]-'0']++;
	}
	if (sz(a)<sz(b)) digA[0] += sz(b)-sz(a);
	else digB[0] += sz(a)-sz(b);
	vector<vi> numPair(10, vi(10));
	dA = digA, dB = digB;
	R0F(k, 10){
		F0R(l, 10){
			int x = min(dA[k], dB[l]);
			dA[k]-=x, dB[l]-=x;
			numPair[k][l] += x;
		}
	}
	int mx = 0;
	F0R(i, 10)F0R(j, 10){
		if (i+j>=10&&digA[i]&&digB[j]){
			vector<vi> tmp(10, vi(10));
			vi A = digA, B = digB;
			int cur = 1;
			tmp[i][j]++;
			A[i]--, B[j]--;
			R0F(k, 10){
				F0R(l, 10){
					if (k+l==9){
						int x = min(A[k], B[l]);
						A[k]-=x, B[l]-=x;
						tmp[k][l] += x;
						cur += x;
					}
					if (k+l>=10){
						int x = min(A[k], B[l]);
						A[k]-=x, B[l]-=x;
						tmp[k][l] += x;
						cur += x;
					}
				}
			}
			R0F(k, 10){
				F0R(l, 10){
					int x = min(A[k], B[l]);
					A[k]-=x, B[l]-=x;
					tmp[k][l] += x;
				}
			}
			if (ckmax(mx, cur)) numPair = tmp;
		}
	}
	dbg(mx, numPair);
	string s, t;
	if (sz(a)>=sz(b)){
		F0R(i, 10) F0R(j, numPair[i][0]) s += '0'+i;
		F0R(i, 10) F0R(j, 10){
			if (i+j==9&&i&&j){
				F0R(k, numPair[i][j]) s+= '0' + i, t += '0'+j;
			}
		}
		F0R(i, 10) F0R(j, 10){
			if (i+j>=10){
				F0R(k, numPair[i][j]) s+= '0' + i, t += '0'+j;
			}
		}
		F0R(i, 10) F0R(j, 10){
			if (i+j<9&&i&&j){
				F0R(k, numPair[i][j]) s+= '0' + i, t += '0'+j;
			}
		}
	}else{
		F0R(i, 10) F0R(j, numPair[0][i]) t += '0'+i;
		F0R(i, 10) F0R(j, 10){
			if (i+j==9&&i&&j){
				F0R(k, numPair[i][j]) s+= '0' + i, t += '0'+j;
			}
		}
		F0R(i, 10) F0R(j, 10){
			if (i+j>=10){
				F0R(k, numPair[i][j]) s+= '0' + i, t += '0'+j;
			}
		}
		F0R(i, 10) F0R(j, 10){
			if (i+j<9&&i&&j){
				F0R(k, numPair[i][j]) s+= '0' + i, t += '0'+j;
			}
		}
	}
	dbg(s, t);
	cout << s << "\n";
	cout << t;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}