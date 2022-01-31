// USACO Guide coming in clutch again
template<typename T, int MAXN>
struct PersistentSegTree{
	struct Node {
		T val;
		Node *l, *r;
	
		Node(ll x) : val(x), l(nullptr), r(nullptr) {}
		Node(Node *ll, Node *rr) : val(0), l(ll), r(rr) {}
	};
	
	T n, a[MAXN]; // The initial array and its size
	Node* roots[MAXN]; // The persistent array's roots
	
	Node* build(int l, int r) {
		if (r-l == 1) return new Node(a[l]);
		int mid = (l + r) / 2;
		return new Node(build(l, mid), build(mid, r));
	}
	
	Node* update(Node* node, T val, int pos, int l, int r) {
		if (r-l == 1) return new Node(val);
		int mid = (l + r) / 2;
		if (pos >= mid) return new Node(node->l, update(node->r, val, pos, mid, r));
		else return new Node(update(node->l, val, pos, l, mid), node->r);
	}
	
	T query(Node* node, int pos, int l, int r) {
		if (r-l == 1) return node->val;
		int mid = (l + r) / 2;
		if (pos >= mid) return query(node->r, pos, mid, r);
		return query(node->l, pos, l, mid);
	}
	
	T get_item(int index, int time) {
		// Gets the array item at a given index and time
		return query(roots[time], index, 0, n);
	}
	
	void update_item(int index, T value, int prev_time, int curr_time) {
		// Updates the array item at a given index and time
		roots[curr_time] = update(roots[prev_time], index, value, 0, n);
	}
	
	PersistentSegTree(int nn, T* init) {
		// Initializes the persistent array, given an input array
		n = nn;
		for (int i = 0; i < n; i++)
			a[i] = init[i];
		roots[0] = build(0, n);
	}
};