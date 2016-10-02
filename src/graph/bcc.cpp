const int MAXN = 100;
vector<pair<int, int>> graph[MAXN];  // { next vertex id, edge id }
int up[MAXN], visit[MAXN], vtime;
vector<int> stk;

vector<int> cut_vertex;     // list of vertex ids
vector<int> bridge;         // list of edge ids
vector<int> bcc_idx[MAXN];  // list of bccids for vertex i
int bcc_cnt;

void dfs(int nod, int par_edge) {
    up[nod] = visit[nod] = ++vtime;
    int child = 0;
    for (const auto& e : graph[nod]) {
        int next = e.first, edge_id = e.second;
        if (edge_id == par_edge) continue;
        if (visit[next] == 0) {
            stk.push_back(next);
            ++child;
            dfs(next, edge_id);
            if (up[next] == visit[next]) bridge.push_back(edge_id);
            if (up[next] >= visit[nod]) {
                ++bcc_cnt;
                do {
                    bcc_idx[stk.back()].push_back(bcc_cnt);
                    stk.pop_back();
                } while (!stk.empty() && stk.back() != nod);
                bcc_idx[nod] = bcc_cnt;
            }
            up[nod] = min(up[nod], up[next]);
        }
        else
            up[nod] = min(up[nod], visit[next]);
    }
    if ((par_edge != -1 && child >= 1 && up[nod] == visit[nod])
        || (par_edge == -1 && child >= 2))
        cut_vertex.push_back(nod);
}

// find BCCs & cut vertexs & bridges in undirected graph
// O(V+E)
void get_bcc() {
    vtime = 0;
    memset(visit, 0, sizeof(visit));
    cut_vertex.clear();
    bridge.clear();
    for (int i = 0; i < n; ++i) bcc_idx[i].clear();
    bcc_cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (visit[i] == 0)
            dfs(i, -1);
    }
}
