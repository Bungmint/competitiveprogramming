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

// THIS ISN'T ACTUALLY TESTED, USE WITH CAUTION
// It was written ported to C++ by SecondThread, a Java main,
// so some debugging might be necessary.
struct Treap {
	int data, priority;
	array<Treap*, 2> kids;
	int subtreeSize, sum=0, toProp=0;

	Treap(int data);
};

int size(Treap *me) {
	return me == NULL ? 0 : me->subtreeSize;
}

void recalc(Treap *me) {
	if (me==NULL) return;
	me->subtreeSize = 1;
	me->sum = me->data + me->toProp*size(me);
	for (Treap* t:me->kids) if (t != NULL) me->subtreeSize += t->subtreeSize;
	for (Treap* t:me->kids) if (t != NULL) me->sum += t->sum+t->toProp*size(t);
}

void prop(Treap *me) {
	if (me==NULL) return;
	if (me->toProp == 0) return;
	for (Treap *t:me->kids) if (t != NULL) t->toProp += me->toProp;
	me->data+=me->toProp;
	me->toProp=0;
	recalc(me);
}

Treap* merge(Treap *l, Treap *r) {
	if (l==NULL) return r;
	if (r==NULL) return l;
	prop(l); prop(r);
	if (l->priority < r->priority) {
		l->kids[1]=merge(l->kids[1], r);
		recalc(l);
		return l;
	}
	else {
		r->kids[0]=merge(l, r->kids[0]);
		recalc(r);
		return r;
	}
}

array<Treap*, 2> split(Treap *me, int nInLeft) {
	if (me == NULL) return {NULL, NULL};
	prop(me);
	if (size(me->kids[0])>=nInLeft) {
		array<Treap*, 2> leftRes=split(me->kids[0], nInLeft);
		me->kids[0]=leftRes[1];
		recalc(me);
		return {leftRes[0], me};
	}
	else {
		nInLeft = nInLeft - size(me->kids[0]) - 1;
		array<Treap*, 2> rightRes = split(me->kids[1], nInLeft);
		me->kids[1] = rightRes[0];
		recalc(me);
		return {me, rightRes[1]};
	}
	return {NULL, NULL};
}

Treap::Treap(int data) {
	kids={NULL, NULL};
	this->data = data;
	this->sum = data;
	this->priority = rng();
	recalc(this);
}

Treap* rangeAdd(Treap* t, int l, int r, int toAdd) {
	array<Treap*, 2> a=split(t, l), b=split(a[1], r-l+1);
	b[0]->toProp+=toAdd;
	return merge(a[0], merge(b[0], b[1]));
}

void solve()
{
	int n;
	cin >> n;
	Treap *t=nullptr;
	for (int i=1;i<=n;i++){
		Treap * s = new Treap(i);
		t = merge(t, s);
	}
	for (int i=1;i<=n;i++){
		int l, r;
		cin >> l >> r;
		if (l>=r) continue;
		if (r-l>=n-r+1){
			int diff = n-r+1;
			dbg(l-1, diff, r-l-diff);
			ar<Treap*, 2> a = split(t, l-1), b = split(a[1], diff), c = split(b[1], r-l-diff);
			t = merge(a[0], merge(c[1], merge(c[0], b[0])));
		}else{
			ar<Treap*,2> a = split(t, l-1), b= split(a[1], r-l), c = split(b[1], r-l);
			
			t = merge(a[0], merge(c[0], merge(b[0], c[1])));
		}
	}
	while(t!=nullptr){
		ar<Treap*, 2> a= split(t,1);
		cout << a[0]->data<<" ";
		t = a[1];
	}
	
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int testcase=1;
    //cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}