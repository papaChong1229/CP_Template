#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Lazy update segment tree (pointer)
template <class T>
class CachedObj {
public:
    void* operator new(size_t s) {
        if (!head) {
            T* a = new T[SIZE];
            for (size_t i = 0; i < SIZE; ++i)
                add(a + i);
        }
        T* p = head;
        head = head->CachedObj<T>::next;
        return p;
    }
    void operator delete(void* p, size_t) {
        if (p) add(static_cast<T*>(p));
    }
    virtual ~CachedObj() {}

protected:
    T* next;

private:
    static T* head;
    static const size_t SIZE;
    static void add(T* p) {
        p->CachedObj<T>::next = head;
        head = p;
    }
};
template <class T>
T* CachedObj<T>::head = 0;
template <class T>
const size_t CachedObj<T>::SIZE = 10000;

template<class T>
class SegmentTree : public CachedObj<SegmentTree> {
private:
    SegmentTree *left, *right;
    T l, r;
    T val, lazy;

    T get() {
        return val;
    }

    void set(T val) {
        this->val = val;
    }

    void add(T val) {
        this->val += val;
    }

    void setLazy(T val) {
        lazy = val;
    }

    void addLazy(T val) {
        lazy += val;
    }

    void pushup() {
        if (left) {
            val = left->get();
        }
        if (right) {
            val += right->get();
        }
    }

    void pushdown() {
        if (lazy == 0) return;

        T mid = l + (r - l) / 2;
        if (!left) left = new SegmentTree(l, mid);
        if (!right) right = new SegmentTree(mid + 1, r);
        left->add(lazy * (mid - l + 1)), right->add(lazy * (r - (mid + 1) + 1));
        left->addLazy(lazy), right->addLazy(lazy);
        lazy = 0;
    }

public:
    SegmentTree()
        : l(0), r(0), val(0), lazy(0), left(nullptr), right(nullptr) {}

    SegmentTree(int l, int r)
        : l(l), r(r), val(0), lazy(0), left(nullptr), right(nullptr) {}

    void add(T L, T R, T val) {
        if (l > R || r < L) return;
        if (L <= l && r <= R) {
            this->val += val * (r - l + 1);
            lazy += val;
            return;
        }

        pushdown();
        T mid = l + (r - l) / 2;
        if (L <= mid) {
            left->add(L, R, val);
        }
        if (mid < R) {
            right->add(L, R, val);
        }
        pushup();
    }

    void update(T L, T R, T val) {
        if (l > R || r < L) return;
        if (L <= l && r <= R) {
            this->val = val * (r - l + 1);
            lazy = val;
            return;
        }

        pushdown();
        T mid = l + (r - l) / 2;
        if (L <= mid) {
            left->update(L, R, val);
        }
        if (mid < R) {
            right->update(L, R, val);
        }
        pushup();
    }

    T query(T L, T R) {
        if (l > R || r < L) return 0;
        if (L <= l && r <= R) return val;

        pushdown();
        T mid = l + (r - l) / 2;
        T res = 0;
        if (L <= mid) {
            res = left->query(L, R);
        }
        if (mid < R) {
            res += right->query(L, R);
        }
        return res;
    }
};


// Lazy update segment tree
template<class T>
class SegmentTree {
private:
    T n;
    vector<T> val, lazy;

    void pushup(T o) {
        val[o] = val[o * 2] + val[o * 2 + 1];
    }

    void pushdown(T o, T l, T r) {
        if (lazy[o] == 0) return;

        T mid = l + (r - l) / 2;
        val[o * 2] += lazy[o] * (mid - l + 1);
        val[o * 2 + 1] += lazy[o] * (r - (mid + 1) + 1);

        lazy[o * 2] += lazy[o];
        lazy[o * 2 + 1] += lazy[o];
        lazy[o] = 0;
    }

    void build(vector<T>& nums, T o, T l, T r) {
        if (l == r) {
            val[o] = nums[l - 1];
            return;
        }

        T mid = l + (r - l) / 2;
        build(nums, o * 2, l, mid);
        build(nums, o * 2 + 1, mid + 1, r);
        pushup(o);
    }

    void add(T o, T l, T r, T L, T R, T val) {
        if (l > R || r < L) return;
        if (L <= l && r <= R) {
            this->val[o] += val * (r - l + 1);
            lazy[o] += val;
            return;
        }

        pushdown(o, l, r);
        T mid = l + (r - l) / 2;
        if (L <= mid) {
            add(o * 2, l, mid, L, R, val);
        }
        if (mid < R) {
            add(o * 2 + 1, mid + 1, r, L, R, val);
        }
        pushup(o);
    }

    void update(T o, T l, T r, T L, T R, T val) {
        if (l > R || r < L) return;
        if (L <= l && r <= R) {
            this->val[o] = val * (r - l + 1);
            lazy[o] = val;
            return;
        }

        pushdown(o, l, r);
        T mid = l + (r - l) / 2;
        if (L <= mid) {
            update(o * 2, l, mid, L, R, val);
        }
        if (mid < R) {
            update(o * 2 + 1, mid + 1, r, L, R, val);
        }
        pushup(o);
    }

    T query(T o, T l, T r, T L, T R) {
        if (l > R || r < L) return 0;
        if (L <= l && r <= R) return val[o];

        pushdown(o, l, r);
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

public:
    SegmentTree(T n) {
        this->n = n;
        val.resize(n * 4);
        lazy.resize(n * 4);
    }

    void build(vector<T>& nums) {
        this->build(nums, 1, 1, n);
    }

    void add(T L, T R, T val) {
        this->add(1, 1, n, L, R, val);
    }

    void update(T L, T R, T val) {
        this->update(1, 1, n, L, R, val);
    }

    T query(T L, T R) {
        return this->query(1, 1, n, L, R);
    }
};