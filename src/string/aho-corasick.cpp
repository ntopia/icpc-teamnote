#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct AhoCorasick
{
    const int alphabet;
    struct node {
        node() {}
        explicit node(int alphabet) : next(alphabet) {}
        vector<int> next, report;
        int back = 0, output_link = 0;
    };
    int maxid = 0;
    vector<node> dfa;
    explicit AhoCorasick(int alphabet) : alphabet(alphabet), dfa(1, node(alphabet)) { }
    template<typename InIt, typename Fn> void add(int id, InIt first, InIt last, Fn func) {
        int cur = 0;
        for ( ; first != last; ++first) {
            auto s = func(*first);
            if (auto next = dfa[cur].next[s]) cur = next;
            else {
                cur = dfa[cur].next[s] = (int)dfa.size();
                dfa.emplace_back(alphabet);
            }
        }
        dfa[cur].report.push_back(id);
        maxid = max(maxid, id);
    }
    void build() {
        queue<int> q;
        vector<char> visit(dfa.size());
        visit[0] = 1;
        q.push(0);
        while(!q.empty()) {
            auto cur = q.front(); q.pop();
            dfa[cur].output_link = dfa[cur].back;
            if (dfa[dfa[cur].back].report.empty())
                dfa[cur].output_link = dfa[dfa[cur].back].output_link;
            for (int s = 0; s < alphabet; s++) {
                auto &next = dfa[cur].next[s];
                if (next == 0) next = dfa[dfa[cur].back].next[s];
                if (visit[next]) continue;
                if (cur) dfa[next].back = dfa[dfa[cur].back].next[s];
                visit[next] = 1;
                q.push(next);
            }
        }
    }
    template<typename InIt, typename Fn> vector<int> countMatch(InIt first, InIt last, Fn func) {
        int cur = 0;
        vector<int> ret(maxid+1);
        for (; first != last; ++first) {
            cur = dfa[cur].next[func(*first)];
            for (int p = cur; p; p = dfa[p].output_link)
                for (auto id : dfa[p].report) ret[id]++;
        }
        return ret;
    }
};
