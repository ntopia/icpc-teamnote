// persistent segment tree impl: sum tree
namespace pstree {
    typedef int val_t;
    const int DEPTH = 18;
    const int TSIZE = 1 << 18;
    const int MAX_QUERY = 262144;

    struct node {
        val_t v;
        node *l, *r;
    } npoll[TSIZE * 2 + MAX_QUERY * DEPTH];

    int pptr, last_q;

    node *head[MAX_QUERY + 1];
    int q[MAX_QUERY + 1];

    void init() {
        memset(&npoll[TSIZE - 1], 0, sizeof(node) * TSIZE); // zero-initialize

        for (int i = TSIZE - 2; i >= 0; i--) {
            npoll[i].v = 0;
            npoll[i].l = &npoll[i*2+1];
            npoll[i].r = &npoll[i*2+2];
        }

        head[0] = &npoll[0];
        last_q = 0;
        pptr = 2 * TSIZE - 1;
        q[0] = 0;
    }

    // update val to pos at time t
    // 0 <= t <= MAX_QUERY, 0 <= pos < TSIZE
    // increasing order
    void update(int pos, int t, int val) {
        head[++last_q] = &npoll[pptr++];
        node *old = head[last_q - 1], *now = head[last_q];
        q[t] = last_q;

        int flag = 1 << DEPTH;
        for (;;) {
            now->v += val;
            flag >>= 1;
            if (flag==0) break;
            if (flag & pos) {
                now->l = old->l;
                now->r = &npoll[pptr++];
                now = now->r, old = old->r;
            } else {
                now->r = old->r;
                now->l = &npoll[pptr++];
                now = now->l, old = old->l;
            }
        }
    }

    val_t query(int s, int e, int l, int r, node *n) {
        if (s == l && e == r) return n->v;
        int m = (l + r) / 2;
        if (m >= e) return query(s, e, l, m, n->l);
        else if (m > s) return query(s, e, m + 1, r, n->r);
        else return query(s, m, l, m, n->l) + query(m + 1, e, m + 1, r, n->r);
    }

    // query summation of [s, e] at time t
    val_t query(int s, int e, int t) {
        if (s > e) return 0; // INVALID
        return query(max(0, s), min(TSIZE - 1, e), 0, TSIZE - 1, head[q[t]]);
    }
}
