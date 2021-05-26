struct segtree
{
    int size;
    ll NO_OP = LINF;
    ll NEUTRAL = 0;
    vector<ll> operations;
    vector<ll> values;

    ll operation(ll a, ll b, ll len)
    {
        if (b == LINF)
            return a;
        return b * len;
    }
    ll calc(ll a, ll b)
    {
        return a + b;
    }
    void opmod(ll &a, ll b, ll len)
    {
        a = operation(a, b, len);
    }

    //void build(int x, int lx, int rx)
    // {
    //     if (rx - lx == 1)
    //     {
    //         values[x] = 1;
    //         return;
    //     }
    //     int m = (lx + rx) / 2;
    //     build(2 * x + 1, lx, m);
    //     build(2 * x + 2, m, rx);
    //     values[x] = calc(values[2 * x + 1], values[2 * x + 2]);
    // }

    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        operations.assign(2 * size, 0LL);
        values.assign(2 * size, 0LL);
        // build(0, 0, size);
    }
    void lazy_propagate(int x, int lx, int rx)
    {
        if (rx - lx == 1)
            return;
        int m = (lx + rx) / 2;
        opmod(operations[2 * x + 1], operations[x], 1);
        opmod(values[2 * x + 1], operations[x], m - lx);
        opmod(operations[2 * x + 2], operations[x], 1);
        opmod(values[2 * x + 2], operations[x], rx - m);
        operations[x] = NO_OP;
    }

    void modify(int l, int r, int v, int x, int lx, int rx)
    {
        lazy_propagate(x, lx, rx);
        if (lx >= r || rx <= l)
            return;
        if (lx >= l && rx <= r)
        {
            opmod(operations[x], v, 1);
            opmod(values[x], v, rx - lx);
            lazy_propagate(x, lx, rx);
            return;
        }
        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);
        values[x] = calc(values[2 * x + 1], values[2 * x + 2]);
        //opmod(values[x], operations[x], rx - lx);
    }

    void modify(int l, int r, int v)
    {
        modify(l, r, v, 0, 0, size);
    }

    ll get(int l, int r, int x, int lx, int rx)
    {
        lazy_propagate(x, lx, rx);
        if (lx >= r || rx <= l)
            return NEUTRAL;
        if (lx >= l && rx <= r)
        {
            return values[x];
        }
        int mid = (lx + rx) / 2;
        ll m1 = get(l, r, 2 * x + 1, lx, mid);
        ll m2 = get(l, r, 2 * x + 2, mid, rx);
        ll res = calc(m1, m2);
        //opmod(res, operations[x], min(rx, r) - max(lx, l));
        return res;
    }

    ll get(int l, int r)
    {
        return get(l, r, 0, 0, size);
    }
} st;