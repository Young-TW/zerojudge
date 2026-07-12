#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

vector<int> head;
vector<int> fail;
vector<int> count;
vector<int> end_node;

struct Edge {
    int to;
    int next;
    char c;
};
vector<Edge> edges;

int trie_size;

void init_trie() {
    trie_size = 1;
    head.assign(1, -1);
    fail.assign(1, 0);
    count.assign(1, 0);
    edges.clear();
}

int get_child(int u, char c) {
    for (int e = head[u]; e != -1; e = edges[e].next) {
        if (edges[e].c == c) {
            return edges[e].to;
        }
    }
    return 0;
}

int add_child(int u, char c) {
    int child = get_child(u, c);
    if (child != 0) {
        return child;
    }
    int new_node = trie_size++;
    head.push_back(-1);
    fail.push_back(0);
    count.push_back(0);
    edges.push_back({new_node, head[u], c});
    head[u] = edges.size() - 1;
    return new_node;
}

void insert(const string& s, int pattern_id) {
    int curr = 0;
    for (char c : s) {
        curr = add_child(curr, c);
    }
    end_node[pattern_id] = curr;
}

vector<int> bfs_order;

void build_fail() {
    bfs_order.clear();
    queue<int> q;
    for (int e = head[0]; e != -1; e = edges[e].next) {
        int child = edges[e].to;
        fail[child] = 0;
        q.push(child);
        bfs_order.push_back(child);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            char c = edges[e].c;
            int f = fail[u];
            while (f != 0 && get_child(f, c) == 0) {
                f = fail[f];
            }
            fail[v] = get_child(f, c);
            if (fail[v] == v) fail[v] = 0;
            q.push(v);
            bfs_order.push_back(v);
        }
    }
}

void search(const string& text) {
    int curr = 0;
    for (char c : text) {
        while (curr != 0 && get_child(curr, c) == 0) {
            curr = fail[curr];
        }
        curr = get_child(curr, c);
        if (curr != 0) {
            count[curr]++;
        }
    }
}

void accumulate_counts() {
    for (int i = bfs_order.size() - 1; i >= 0; i--) {
        int u = bfs_order[i];
        count[fail[u]] += count[u];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string text;
    while (cin >> text) {
        int N;
        cin >> N;
        vector<string> patterns(N);
        end_node.resize(N);
        init_trie();
        for (int i = 0; i < N; i++) {
            cin >> patterns[i];
            insert(patterns[i], i);
        }
        build_fail();
        search(text);
        accumulate_counts();
        for (int i = 0; i < N; i++) {
            cout << count[end_node[i]] << "\n";
        }
    }
    return 0;
}
