#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class T>
class SegmentTree {
private:
    T n;
    vector<T> val;

    void pushup(T o) {
        val[o] = val[o * 2] + val[o * 2 + 1];
    }

    void build(vector<T>& nums, int o, int l, int r) {
        if (l == r) {
            val[o] = nums[l - 1];
            return;
        }

        T mid = l + (r - l) / 2;
        build(nums, o * 2, l, mid);
        build(nums, o * 2 + 1, mid + 1, r);
        pushup(o);
    }

    void add(T o, T l, T r, T idx, T val) {
        if (l == r) {
            this->val[o] += val;
            return;
        }

        T mid = l + (r - l) / 2;
        if (idx <= mid) {
            add(o * 2, l, mid, idx, val);
        } else {
            add(o * 2 + 1, mid + 1, r, idx, val);
        }
        pushup(o);
    }

    void update(T o, T l, T r, T idx, T val) {
        if (l == r) {
            this->val[o] = val;
            return;
        }

        T mid = l + (r - l) / 2;
        if (idx <= mid) {
            update(o * 2, l, mid, idx, val);
        } else {
            update(o * 2 + 1, mid + 1, r, idx, val);
        }
        pushup(o);
    }

    T query(T o, T l, T r, T L, T R) {
        if (l > R || r < L) return 0;
        if (L <= l && r <= R) return val[o];

        T mid = l + (r - l) / 2;
        T res = 0;
        if (L <= mid) {
            res = query(o * 2, l, mid, L, R);
        } 
        if (mid < R) {
            res += query(o * 2 + 1, mid + 1, r, L, R);
        }
        return res;
    }

    T queryIdxUpper(T o, T l, T r, T L, T R, T val) {
        if (l > R || r < L) {
            return -1;
        }
        else if (this->val[o] <= val) {
            return -1;
        }
        else if (l == r) {
            return l - 1;
        }

        T mid = l + (r - l) / 2;
        if (L <= mid) {
            T res = queryIdxUpper(o * 2, l, mid, L, R, val);
            if (res != -1) {
                return res;
            }
        }
        return queryIdxUpper(o * 2 + 1, mid + 1, r, L, R, val);
    }

    T queryIdxLower(T o, T l, T r, T L, T R, T val) {
        if (l > R || r < L) {
            return -1;
        }
        else if (this->val[o] < val) {
            return -1;
        }
        else if (l == r) {
            return l - 1;
        }

        T mid = l + (r - l) / 2;
        if (L <= mid) {
            T res = queryIdxLower(o * 2, l, mid, L, R, val);
            if (res != -1) {
                return res;
            }
        }
        return queryIdxLower(o * 2 + 1, mid + 1, r, L, R, val);
    }

public:
    SegmentTree(T n) {
        this->n = n;
        val.resize(n * 4);
    }

    void build(vector<T>& nums) {
        this->build(nums, 1, 1, n);
    }

    void update(T idx, T val) {
        this->update(1, 1, n, idx, val);
    }
    
    void add(T idx, T val) {
        this->update(1, 1, n, idx, val);
    }

    T query(T L, T R) {
        return this->query(1, 1, n, L, R);
    }

    T queryIdxUpper(T L, T R, T val) {
        return this->queryIdxUpper(1, 1, n, L, R, val);
    }

    T queryIdxLower(T L, T R, T val) {
        return this->queryIdxLower(1, 1, n, L, R, val);
    }
};