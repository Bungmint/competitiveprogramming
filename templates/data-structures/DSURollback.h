// TODO: test imp
/**
 * Disjoint Set Union with rollback
 * Source: USACO Guide/Benq
 * Verification:
 * Time complexity: amortized O(logn) updates/queries
 */

struct DSU {
	vector<int> e;
	vector<int> mem;
	vector<pair<pii, pii>> ev;
	DSU(int N) { e = vector<int>(N, -1); }
	int get(int x) { return e[x] < 0 ? x : get(e[x]); }
	bool same_set(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) {
		x = get(x), y = get(y);
		if (x == y) return false;
		ev.pb({{x, e[x]}, {y, e[y]}});
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
		return true;
	}
	void snapshot(){ mem.pb(sz(ev)); }
	void rollback(){
		if (mem.empty()) return;
		int SZ = mem.back();
		mem.pop_back();
		while(sz(ev) != SZ){
			pair<pii, pii> p = ev.back();
			e[p.fi.fi] = p.fi.se;
			e[p.se.fi] = p.se.se;
			ev.pop_back();
		}
	}
};