#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string src, tgt;

void dfs(int src_idx, int tgt_idx, string& stk, string& ops) {
    if (tgt_idx == (int)tgt.length()) {
        for (int i = 0; i < (int)ops.length(); ++i) {
            if (i > 0) cout << " ";
            cout << ops[i];
        }
        cout << "\n";
        return;
    }

    if (src_idx < (int)src.length()) {
        stk.push_back(src[src_idx]);
        ops.push_back('i');
        dfs(src_idx + 1, tgt_idx, stk, ops);
        ops.pop_back();
        stk.pop_back();
    }

    if (!stk.empty() && stk.back() == tgt[tgt_idx]) {
        char c = stk.back();
        stk.pop_back();
        ops.push_back('o');
        dfs(src_idx, tgt_idx + 1, stk, ops);
        ops.pop_back();
        stk.push_back(c);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> src >> tgt) {
        cout << "[\n";
        bool possible = true;
        if (src.length() != tgt.length()) {
            possible = false;
        } else {
            string s1 = src;
            string s2 = tgt;
            sort(s1.begin(), s1.end());
            sort(s2.begin(), s2.end());
            if (s1 != s2) possible = false;
        }
        if (possible) {
            string stk = "";
            string ops = "";
            dfs(0, 0, stk, ops);
        }
        cout << "]\n";
    }
    return 0;
}
