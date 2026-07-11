#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<int> op_type(1, -1); // 1-indexed, dummy at index 0
    vector<int> op_val(1, 0);
    int type;
    while (cin >> type) {
        if (type == 0) {
            int v; cin >> v;
            op_type.push_back(0);
            op_val.push_back(v);
        } else if (type == 1) {
            int x; cin >> x;
            op_type.push_back(1);
            op_val.push_back(x);
        } else if (type == 2) {
            op_type.push_back(2);
            op_val.push_back(0);
        } else if (type == 3) {
            op_type.push_back(3);
            op_val.push_back(0);
        }
    }
    int Q = (int)op_type.size() - 1;
    if (Q == 0) return 0;
    
    vector<vector<int>> children(Q + 1);
    for (int i = 1; i <= Q; ++i) {
        int parent = (op_type[i] == 0) ? op_val[i] : i - 1;
        children[parent].push_back(i);
    }
    
    vector<int> val(Q + 5);
    vector<int> prev(Q + 5);
    vector<int> nxt(Q + 5);
    vector<int> popped_val(Q + 1, 0);
    vector<string> ans(Q + 1);
    int head = 0, tail = 0, sz = 0;
    int node_cnt = 0;
    
    auto push_back = [&](int x) {
        ++node_cnt;
        int cur = node_cnt;
        val[cur] = x;
        prev[cur] = tail;
        nxt[cur] = 0;
        if (tail == 0) {
            head = tail = cur;
        } else {
            nxt[tail] = cur;
            tail = cur;
        }
        ++sz;
    };
    
    auto pop_front = [&]() -> int {
        int cur = head;
        int x = val[cur];
        head = nxt[cur];
        if (head == 0) tail = 0;
        else prev[head] = 0;
        --sz;
        return x;
    };
    
    auto undo_push_back = [&]() {
        int cur = tail;
        tail = prev[cur];
        if (tail == 0) head = 0;
        else nxt[tail] = 0;
        --sz;
    };
    
    auto undo_pop_front = [&](int x) {
        ++node_cnt;
        int cur = node_cnt;
        val[cur] = x;
        nxt[cur] = head;
        prev[cur] = 0;
        if (head == 0) {
            head = tail = cur;
        } else {
            prev[head] = cur;
            head = cur;
        }
        ++sz;
    };
    
    auto record_ans = [&](int v) {
        if (sz == 0) {
            ans[v] = "";
        } else {
            string s;
            int cur = head;
            for (int i = 0; i < 3 && cur != 0; ++i) {
                s += "<";
                s += to_string(val[cur]);
                cur = nxt[cur];
            }
            if (sz > 3) s += "<...";
            ans[v] = s;
        }
    };
    
    vector<pair<int, int>> st;
    st.reserve(2 * Q + 5);
    st.push_back(make_pair(0, 0));
    while (!st.empty()) {
        pair<int, int> p = st.back();
        st.pop_back();
        int v = p.first;
        int state = p.second;
        if (state == 0) {
            // enter
            if (v != 0) {
                if (op_type[v] == 1) {
                    push_back(op_val[v]);
                } else if (op_type[v] == 2) {
                    popped_val[v] = pop_front();
                }
            }
            if (op_type[v] == 3) {
                record_ans(v);
            }
            st.push_back(make_pair(v, 1));
            for (int i = (int)children[v].size() - 1; i >= 0; --i) {
                st.push_back(make_pair(children[v][i], 0));
            }
        } else {
            // exit
            if (v != 0) {
                if (op_type[v] == 1) {
                    undo_push_back();
                } else if (op_type[v] == 2) {
                    undo_pop_front(popped_val[v]);
                }
            }
        }
    }
    
    for (int i = 1; i <= Q; ++i) {
        if (op_type[i] == 3) {
            cout << ans[i] << '\n';
        }
    }
    
    return 0;
}
