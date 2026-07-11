#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        map<string, int> tree;
        bool complete = true;
        while (s != "()") {
            size_t comma = s.find(',');
            if (comma != string::npos) {
                int val = stoi(s.substr(1, comma - 1));
                string path = s.substr(comma + 1, s.length() - comma - 2);
                if (tree.count(path)) {
                    complete = false;
                }
                tree[path] = val;
            }
            if (!(cin >> s)) break;
        }
        
        if (s != "()") break;
        
        for (auto const& pair : tree) {
            if (pair.first == "") continue;
            string parent = pair.first.substr(0, pair.first.length() - 1);
            if (!tree.count(parent)) {
                complete = false;
                break;
            }
        }
        
        if (!complete || !tree.count("")) {
            cout << "not complete\n";
        } else {
            queue<string> q;
            q.push("");
            vector<int> ans;
            while (!q.empty()) {
                string curr = q.front();
                q.pop();
                ans.push_back(tree[curr]);
                string left = curr + "L";
                string right = curr + "R";
                if (tree.count(left)) q.push(left);
                if (tree.count(right)) q.push(right);
            }
            
            for (size_t i = 0; i < ans.size(); ++i) {
                if (i > 0) cout << " ";
                cout << ans[i];
            }
            cout << "\n";
        }
    }
    return 0;
}
