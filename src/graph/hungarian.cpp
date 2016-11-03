namespace hung {
    /*
    * alternative cost_t example
    *
    typedef pair<int,int> cost_t;
    cost_t MAX_COST = make_pair(2,0);
    pair<int,int> &operator += (pair<int,int> &a, const pair<int,int> &b) {
        a.first += b.first; a.second += b.second;
        return a;
    }
    pair<int,int> &operator -= (pair<int,int> &a, const pair<int,int> &b) {
        a.first -= b.first; a.second -= b.second;
        return a;
    }
    */
    typedef int cost_t;
    cost_t MAX_COST = numeric_limits<cost_t>::max() / 2;
    // input: n, dat(which is NOT const)
    // output: call solve(), match, matched
    // minimum matching 계산이다.
    const int MAX_N = 500;

    int n, match[MAX_N], matched[MAX_N];
    cost_t dat[MAX_N][MAX_N];
    int q[MAX_N], v[MAX_N], vcnt;
    int f[MAX_N], reach[MAX_N], reach2[MAX_N], rcnt;

    int augment(int r) {
        int h, t = 0;
        v[r] = ++vcnt;
        q[t++] = r;
        for (h = 0; h<t; h++) {
            int qh = q[h];
            for (int j = 0; j<n; j++) {
                if (dat[qh][j] != 0) continue;
                int next = matched[j];
                if (next == -1) {
                    for (;;) {
                        int org = match[qh];
                        match[qh] = j; matched[j] = qh;
                        if (qh == r) return 1;
                        qh = f[qh]; j = org;
                    }
                }
                else if (v[next] != vcnt) {
                    v[next] = vcnt, f[next] = qh, q[t++] = next;
                }
            }
        }
        for (int i = 0; i<n; i++)
            if (v[i] == vcnt) {
                reach[i] = rcnt;
                if (i != r) reach2[match[i]] = rcnt;
            }
        return 0;
    }

    cost_t solve() {
        cost_t ans = 0;
        for (int i = 0; i<n; i++) match[i] = matched[i] = -1;
        for (int i = 0; i<n; i++) {
            cost_t minv = *min_element(dat[i], dat[i] + n);
            for (int j = 0; j < n; j++) dat[i][j] -= minv;
            ans += minv;
            minv = dat[0][i];
            for (int j = 1; j<n; j++) minv = min(minv, dat[j][i]);
            for (int j = 0; j<n; j++) dat[j][i] -= minv;
            ans += minv;
        }
        for (;;) {
            ++rcnt;
            bool needMore = false;
            for (int i = 0; i<n; i++) {
                if (match[i] >= 0) continue;
                if (!augment(i)) needMore = true;
            }
            if (!needMore) break;
            cost_t minv = MAX_COST;
            for (int i = 0; i<n; i++) {
                if (reach[i] != rcnt) continue;
                for (int j = 0; j<n; j++) {
                    if (reach2[j] == rcnt) continue;
                    minv = min(minv, dat[i][j]);
                }
            }
            for (int i = 0; i<n; i++) {
                if (match[i]<0) ans += minv;
                for (int j = 0; j<n; j++) {
                    if (reach[i] != rcnt) dat[i][j] += minv;
                    if (reach2[j] != rcnt) dat[i][j] -= minv;
                }
            }
        }
        return ans;
    }
}
