#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <array>
#include <cstdint>

using namespace std;

class AhoCorasick {
private:
    vector<int> head;
    vector<int> fail;
    vector<int> sum_cnt;
    vector<char> terminal;
    vector<int> to;
    vector<uint8_t> ch;
    vector<int> nxt;
    array<int, 62> root_trans;
    int node_cnt;
    int edge_cnt;

    inline int char_to_idx(char c) const {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
        return c - 'a' + 36;
    }

    inline int get_child(int u, int c) const {
        for (int e = head[u]; e != -1; e = nxt[e]) {
            if (ch[e] == c) return to[e];
        }
        return -1;
    }

public:
    AhoCorasick(int max_nodes = 0, int max_edges = 0) {
        head.reserve(max_nodes);
        fail.reserve(max_nodes);
        sum_cnt.reserve(max_nodes);
        terminal.reserve(max_nodes);
        to.reserve(max_edges);
        ch.reserve(max_edges);
        nxt.reserve(max_edges);
        init();
    }

    void init() {
        head.clear(); fail.clear(); sum_cnt.clear(); terminal.clear();
        to.clear(); ch.clear(); nxt.clear();
        root_trans.fill(-1);
        node_cnt = 1;
        edge_cnt = 0;
        head.push_back(-1); // root
        fail.push_back(0);
        sum_cnt.push_back(0);
        terminal.push_back(0);
    }

    void insert(const string& s) {
        int u = 0;
        for (char c : s) {
            int idx = char_to_idx(c);
            int v = get_child(u, idx);
            if (v == -1) {
                v = node_cnt++;
                head.push_back(-1);
                fail.push_back(0);
                sum_cnt.push_back(0);
                terminal.push_back(0);
                to.push_back(v);
                ch.push_back(idx);
                nxt.push_back(head[u]);
                head[u] = edge_cnt++;
            }
            u = v;
        }
        terminal[u] = 1;
    }

    void build() {
        for (int e = head[0]; e != -1; e = nxt[e]) {
            root_trans[ch[e]] = to[e];
        }

        queue<int> q;
        for (int e = head[0]; e != -1; e = nxt[e]) {
            int v = to[e];
            fail[v] = 0;
            q.push(v);
        }
        fail[0] = 0;
        sum_cnt[0] = terminal[0];
        while (!q.empty()) {
            int u = q.front(); q.pop();
            sum_cnt[u] = terminal[u] + sum_cnt[fail[u]];
            for (int e = head[u]; e != -1; e = nxt[e]) {
                int v = to[e];
                int c = ch[e];
                int f = fail[u];
                while (true) {
                    int nxt_v = get_child(f, c);
                    if (nxt_v != -1) {
                        fail[v] = nxt_v;
                        break;
                    }
                    if (f == 0) {
                        fail[v] = 0;
                        break;
                    }
                    f = fail[f];
                }
                q.push(v);
            }
        }
    }

    long long query(const string& s) const {
        long long ans = 0;
        int u = 0;
        for (char c : s) {
            int idx = char_to_idx(c);
            while (u != 0) {
                int v = get_child(u, idx);
                if (v != -1) {
                    u = v;
                    break;
                }
                u = fail[u];
            }
            if (u == 0) {
                int v = root_trans[idx];
                if (v != -1) u = v;
            }
            ans += sum_cnt[u];
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int MAX_NODES = 2000005;
    int N;
    int caseNum = 1;
    while (cin >> N) {
        AhoCorasick ac(MAX_NODES, MAX_NODES);
        for (int i = 0; i < N; ++i) {
            string w;
            cin >> w;
            ac.insert(w);
        }
        ac.build();
        int Q;
        cin >> Q;
        cout << "Case #" << caseNum++ << ":\n";
        for (int i = 0; i < Q; ++i) {
            string s;
            cin >> s;
            cout << ac.query(s) << '\n';
        }
    }
    return 0;
}
