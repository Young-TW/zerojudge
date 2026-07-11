#include <iostream>
#include <unordered_map>
#include <chrono>
#include <cstdint>

using namespace std;

const int MAXM = 100005;
int prev_node[MAXM];
int next_node[MAXM];
long long node_id[MAXM];
long long node_val[MAXM];
int head = -1;
int tail = -1;
int node_cnt = 0;

void remove_node(int u) {
    if (prev_node[u] != -1) {
        next_node[prev_node[u]] = next_node[u];
    } else {
        head = next_node[u];
    }
    if (next_node[u] != -1) {
        prev_node[next_node[u]] = prev_node[u];
    } else {
        tail = prev_node[u];
    }
}

void push_front(int u) {
    prev_node[u] = -1;
    next_node[u] = head;
    if (head != -1) {
        prev_node[head] = u;
    } else {
        tail = u;
    }
    head = u;
}

void move_to_front(int u) {
    if (head == u) return;
    remove_node(u);
    push_front(u);
}

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

unordered_map<long long, int, custom_hash> id_to_node;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int M;
    if (!(cin >> M)) return 0;

    int op;
    while (cin >> op) {
        if (op == 0) {
            long long x;
            cin >> x;
            auto it = id_to_node.find(x);
            if (it != id_to_node.end()) {
                int node = it->second;
                move_to_front(node);
                cout << node << " " << node_val[node] << "\n";
            } else {
                int node;
                long long val = 0;
                if (node_cnt < M) {
                    node = node_cnt++;
                    node_id[node] = x;
                    node_val[node] = val;
                    id_to_node[x] = node;
                    push_front(node);
                } else {
                    node = tail;
                    long long old_id = node_id[node];
                    id_to_node.erase(old_id);
                    node_id[node] = x;
                    node_val[node] = val;
                    id_to_node[x] = node;
                    move_to_front(node);
                }
                cout << node << " " << node_val[node] << "\n";
            }
        } else if (op == 1) {
            long long x, y;
            cin >> x >> y;
            auto it = id_to_node.find(x);
            if (it != id_to_node.end()) {
                int node = it->second;
                move_to_front(node);
                node_val[node] = y;
            } else {
                int node;
                long long val = y;
                if (node_cnt < M) {
                    node = node_cnt++;
                    node_id[node] = x;
                    node_val[node] = val;
                    id_to_node[x] = node;
                    push_front(node);
                } else {
                    node = tail;
                    long long old_id = node_id[node];
                    id_to_node.erase(old_id);
                    node_id[node] = x;
                    node_val[node] = val;
                    id_to_node[x] = node;
                    move_to_front(node);
                }
            }
        }
    }

    return 0;
}
