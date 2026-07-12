#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <sstream>

using namespace std;

int main() {
    string line;
    map<int, vector<int>> adj = {
        {1, {2, 7}},
        {2, {3, 4}},
        {3, {7}},
        {4, {5}},
        {7, {8}},
        {9, {10}},
        {10, {11}}
    };
    map<int, int> calls = {
        {11, 12},
        {5, 6},
        {6, 7}
    };
    int return_node = 8;
    int end_node = 12;

    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<int> path;
        int x;
        while (ss >> x) {
            path.push_back(x);
        }
        if (path.size() == 1 && path[0] == 0) break;
        if (path.empty()) continue;

        bool valid = true;
        stack<int> st;

        if (path[0] != 9) {
            valid = false;
        }

        for (size_t i = 0; i < path.size() - 1 && valid; ++i) {
            int u = path[i];
            int v = path[i + 1];

            if (calls.count(u)) {
                if (v != 1) {
                    valid = false;
                } else {
                    st.push(calls[u]);
                }
            } else if (u == return_node) {
                if (st.empty() || v != st.top()) {
                    valid = false;
                } else {
                    st.pop();
                }
            } else {
                if (adj.count(u)) {
                    bool found = false;
                    for (int neighbor : adj[u]) {
                        if (neighbor == v) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        valid = false;
                    }
                } else {
                    valid = false;
                }
            }
        }

        if (valid) {
            if (path.back() != end_node || !st.empty()) {
                valid = false;
            }
        }

        cout << (valid ? "valid" : "invalid") << endl;
    }

    return 0;
}
