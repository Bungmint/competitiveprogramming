#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
#define sz(x) (int)(x).size()

template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
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

struct custom_hash
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
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353

struct str{
	ar<bool,3> pref = {0,0,0};
	ar<bool,3> suf = {0,0,0};
	long long occ = 0;
	ll len=0;
	string front = "";
	string back = "";
};

ll calc(str st1, str st2){
	dbg(st1.suf, st2.pref);
	return ((st1.suf[0]&&st2.pref[0])+(st1.suf[1]&&st2.pref[1])+(st1.suf[2]&&st2.pref[2]));
}

void solve()
{
	int n;
	cin >> n;
	map<string, str> m1;
	string res;
	for (int i=0;i<n;i++){
		string s, op;
		cin >> s >> op;
		if (i==n-1) res = s;
		if (op==":="){
			string acc;
			cin >> acc;
			ll leng = acc.length();
			str val;
			if (acc[0]=='a') val.pref[1] = 1;
			if (acc[acc.length()-1]=='h') val.suf[0] = 1;
			if (leng>=3&&acc.substr(0,3)=="aha") val.pref[0] = 1;
			if (leng>=3&&acc.substr(leng-3,3)=="hah") val.suf[1] = 1;
			if (leng>=2&&acc.substr(0,2)=="ha") val.pref[2] = 1;
			if (leng>=2&&acc.substr(leng-2, 2)=="ha") val.suf[2] = 1;
			for (int j=0;j<leng-3;j++){
				if (acc.substr(j, 4)=="haha") val.occ++;
			}
			if (leng>=3) val.front = acc.substr(0,3), val.back = acc.substr(leng-3,3);
			else val.front = acc, val.back = acc;
			val.len = leng;
			m1[s] = val;
			dbg(acc);
			dbg(val.pref, val.suf, val.occ, val.len,val.front, val.back);
		}else{
			string t1, t2,tmp;
			cin >> t1  >>tmp>> t2;
			str cur1 = m1[t1], cur2 = m1[t2];
			str ans;
			ans.occ = cur1.occ+cur2.occ+calc(cur1,cur2);
			dbg(ans.occ);
			string acc = cur1.front + cur2.front;
			if (acc[0]=='a') ans.pref[1] = 1;
			if (acc.length()>=3&&acc.substr(0,3)=="aha") ans.pref[0] = 1;
			if (acc.length()>=2&&acc.substr(0,2)=="ha") ans.pref[2] = 1;
			if (acc.length()>=3) ans.front = acc.substr(0,3);
			else ans.front = acc;
			
			dbg();
			acc = cur1.back+cur2.back;
			dbg(acc);
			int leng = acc.length();
			if (acc[leng-1]=='h') ans.suf[0] = 1;
			if (leng>=3&&acc.substr(leng-3,3)=="hah") ans.suf[1] = 1;
			if (leng>=2&&acc.substr(leng-2, 2)=="ha") ans.suf[2] = 1;
			if (acc.length()>=3) ans.back = acc.substr(acc.length()-3,3);
			else ans.back = acc;
			
			
			ans.len = cur1.len+cur2.len;
			m1[s] = ans;
		}
	}
	cout << m1[res].occ << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}