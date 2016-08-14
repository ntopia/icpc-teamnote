const int MAXN = 100;
vector<int> graph[MAXN], grev[MAXN];
int visit[MAXN], vcnt;
int scc_idx[MAXN], scc_cnt;
vector<int> emit;

void dfs(int nod, vector<int> graph[]) {
    visit[nod] = vcnt;
    for (int next : graph[nod]) {
        if (visit[next] == vcnt) continue;
        dfs(next, graph);
    }
    emit.push_back(nod);
}

// find SCCs in given graph
// O(V+E)
void get_scc() {
    scc_cnt = 0;
    vcnt = 1;
    emit.clear();
    memset(visit, 0, sizeof(visit));

    for (int i = 0; i < n; i++) {
        if (visit[i] == vcnt) continue;
        dfs(i, graph);
    }

    ++vcnt;
    for (auto st : vector<int>(emit.rbegin(), emit.rend())) {
        if (visit[st] == vcnt) continue;
        emit.clear();
        dfs(st, grev);
        ++scc_cnt;
        for (auto node : emit)
            scc_idx[node] = scc_cnt;
    }
}
