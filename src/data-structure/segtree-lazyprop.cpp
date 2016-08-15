// example implementation of sum tree

const int TSIZE = 131072; // always 2^k form && n <= TSIZE
int segtree[TSIZE * 2 + 1], pending[TSIZE * 2 + 1];
const int EMPTY = 0;
void seg_init(int nod, int l, int r) {
    if (l == r) segtree[nod] = dat[l];
    else {
        int m = (l + r) >> 1;
        seg_init(nod << 1, l, m);
        seg_init(nod << 1 | 1, m + 1, r);
        segtree[nod] = segtree[nod << 1] + segtree[nod << 1 | 1];
    }
}
void seg_relax(int nod, int l, int r) {
    if (pending[nod] != EMPTY) {
        segtree[nod] += (r - l + 1) * pending[nod];
        if (l < r) {
            pending[nod << 1] += pending[nod];
            pending[nod << 1 | 1] += pending[nod];
        }
        pending[nod] = EMPTY;
    }
}
int seg_query(int nod, int l, int r, int s, int e) {
    if (r < s || e < l) return 0;
    seg_relax(nod, l, r);
    if (s <= l && r <= e) return segtree[nod];
    int m = (l + r) >> 1;
    return seg_query(nod << 1, l, m, s, e) + seg_query(nod << 1 | 1, m + 1, r, s, e);
}
void seg_update(int nod, int l, int r, int s, int e, int val) {
    seg_relax(nod, l, r);
    if (r < s || e < l) return;
    if (s <= l && r <= e) {
        pending[nod] += val;
        seg_relax(nod, l, r);
        return;
    }
    int m = (l + r) >> 1;
    seg_update(nod << 1, l, m, s, e, val);
    seg_update(nod << 1 | 1, m + 1, r, s, e, val);
    segtree[nod] = segtree[nod << 1] + segtree[nod << 1 | 1];
}
