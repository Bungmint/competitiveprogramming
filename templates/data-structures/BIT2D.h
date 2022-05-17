/**
 * Description: 2D Binary Indexed Tree
 * Source: Own
 * Verification: https://cses.fi/problemset/task/1739
 * Time complexity: O(log^2 n) update/query
 * Memory complexity: O(n^2)
 * O-indexing
 */
template <typename T>
struct BIT2D {
    vector<vector<T>> bit;
    int N;
    BIT2D(int n) : N(n) {
        bit.resize(n + 1);
        for (auto &v : bit) v.resize(n + 1);
    }
    void upd(int x, int y, T v) {
        for (x++; x <= N; x += x & -x) {
            for (int i = y + 1; i <= N; i += i & -i) {
                bit[x][i] += v;
            }
        }
    } 
    T query(int x, int y) {
        T res = T();
        for (x++; x; x -= x & -x) {
            for (int i = y + 1; i; i -= i & -i) {
                res += bit[x][i];
            }
        }
        return res;
    }
    T query(int x1, int x2, int y1, int y2) {
        return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
    }
};