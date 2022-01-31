// Problem: Substring Order I
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/2108
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
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
#define dbg(...)
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

const int MX=1e5+3, MK = 26;
int s[MX], sa[MX],ch[MX], lcp[MX];
string S;

//https://www.cs.helsinki.fi/u/tpkarkka/publications/icalp03.pdf
//Simple Linear Work Suffix Array Construction* - Juha Kärkkäinen and Peter Sanders
//Max Planck Institut
inline bool leq(int a1, int a2, int b1, int b2) // lexicographic order
{return(a1 < b1 || a1 == b1 && a2 <= b2); } // for pairs
inline bool leq(int a1, int a2, int a3, int b1, int b2, int b3)
{return(a1 < b1 || a1 == b1 && leq(a2,a3, b2,b3)); } // and triples


// stably sort a[0..n-1] to b[0..n-1] with keys in 0..K from r
static void radixPass(int* a, int* b, int* r, int n, int K)
{// count occurrences
	int* c = new int[K + 1]; // counter array
	for (int i = 0; i <= K; i++) c[i] = 0; // reset counters
	for (int i = 0; i < n; i++) c[r[a[i]]]++; // count occurrences
	for (int i = 0, sum = 0; i <= K; i++) // exclusive prefix sums
	{int t = c[i]; c[i] = sum; sum += t; }
	for (int i = 0; i < n; i++) b[c[r[a[i]]]++] = a[i]; // sort
	delete [] c;
}
// find the suffix array SA of s[0..n-1] in {1..K}ˆn
// require s[n]=s[n+1]=s[n+2]=0, n>=2
void suffixArray(int* s, int* SA, int n, int K) {
	int n0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2;
	int* s12 = new int[n02 + 3]; s12[n02]= s12[n02+1]= s12[n02+2]=0;
	int* SA12 = new int[n02 + 3]; SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
	int* s0 = new int[n0];
	int* SA0 = new int[n0];
	// generate positions of mod 1 and mod 2 suffixes
	// the "+(n0-n1)" adds a dummy mod 1 suffix if n%3 == 1
	for (int i=0, j=0; i < n+(n0-n1); i++) if (i%3 != 0) s12[j++] = i;
	// lsb radix sort the mod 1 and mod 2 triples
	radixPass(s12 , SA12, s+2, n02, K);
	radixPass(SA12, s12 , s+1, n02, K);
	radixPass(s12 , SA12, s , n02, K);
	// find lexicographic names of triples
	int name = 0, c0 = -1, c1 = -1, c2 = -1;
	for (int i = 0; i < n02; i++) {
		if (s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2)
		{name++; c0 = s[SA12[i]]; c1 = s[SA12[i]+1]; c2 = s[SA12[i]+2]; }
		if (SA12[i] % 3 == 1) { s12[SA12[i]/3] = name; } // left half
		else {s12[SA12[i]/3 + n0] = name; } // right half
	}
	// recurse if names are not yet unique
	if (name < n02) {
	suffixArray(s12, SA12, n02, name);
		// store unique names in s12 using the suffix array
		for (int i = 0; i < n02; i++) s12[SA12[i]] = i + 1;
	} else // generate the suffix array of s12 directly
		for (int i = 0; i < n02; i++) SA12[s12[i] - 1] = i;
	
	// stably sort the mod 0 suffixes from SA12 by their first character
	for (int i=0, j=0; i < n02; i++) if (SA12[i] < n0) s0[j++] = 3*SA12[i];
	radixPass(s0, SA0, s, n0, K);
	// merge sorted SA0 suffixes and sorted SA12 suffixes
	for (int p=0, t=n0-n1, k=0; k < n; k++) {
		#define GetI() (SA12[t] < n0 ? SA12[t]*3+1: (SA12[t] - n0) * 3 + 2)
		int i = GetI(); // pos of current offset 12 suffix
		int j = SA0[p]; // pos of current offset 0 suffix
		if (SA12[t] < n0 ? // different compares for mod 1 and mod 2 suffixes
		leq(s[i], s12[SA12[t] + n0], s[j], s12[j/3]) :
		leq(s[i],s[i+1],s12[SA12[t]-n0+1], s[j],s[j+1],s12[j/3+n0]))
		{// suffix from SA12 is smaller
		SA[k] = i; t++;
		if (t == n02) // done --- only SA0 suffixes left
		for (k++; p < n0; p++, k++) SA[k] = SA0[p];
		} else {// suffix from SA0 is smaller
			SA[k] = j; p++;
			if (p == n0) // done --- only SA12 suffixes left
			for (k++; t < n02; t++, k++) SA[k] = GetI();
		}
	}
	delete [] s12; delete [] SA12; delete [] SA0; delete [] s0;
}
void lcp_construction(string const& str) {
	int n = sz(str);
	F0R(i, n) ch[sa[i]] = i;
    int k = 0;
    F0R(i,n) {
        if (ch[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[ch[i] + 1];
        while (i + k < n && j + k < n && str[i+k] == str[j+k])
            k++;
        lcp[ch[i]] = k;
        if (k)
            k--;
    }
}

void solve()
{
	cin >> S;
	ll k;cin >> k;
	int n = sz(S);
	F0R(i, n) s[i] = S[i]-'a'+1;
	suffixArray(s, sa, n, MK);
	lcp_construction(S);
	ll sum = 0;
	F0R(i, n){
		int cur = n-sa[i];
		if (i) cur-=lcp[i-1];
		if (sum+cur>=k){
			ll st = sa[i], en = sa[i]-1LL+k-sum;
			if (i)en+=lcp[i-1];
			dbg(st,en);
			FOR(i,st,en+1)cout << S[i];
			return;
		}else sum+= cur;
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}