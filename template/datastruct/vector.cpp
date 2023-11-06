template <class T>
struct myvec {
    T *v;
    int sz, dsz;
    myvec() { v = NULL, sz = dsz = 0; }
    ~myvec() { free(v); }
    operator T *() const { return v; }
    void rsz(int x) { v = (T *)realloc(v, sizeof(T) * (dsz = sz = x)); }
    void pb(T x) {
        if (sz == dsz) v = (T *)realloc(v, sizeof(T) * (dsz = dsz << 1 | 1));
        v[sz++] = x;
    }
    void fill(T x) {
        for (int i = 0; i < sz; i++) v[i] = x;
    }
};
