#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

int N;
vector<string> idioms;
vector<int> adj[45];
bool used[45];
vector<int> current_path;
vector<vector<int>> all_max_paths;
int max_len = 0;

// 取得字串最後一個字 (UTF-8 中文，四字成語，假設每個中文字 3 bytes)
// 四字成語共 12 bytes，最後一個字從 index 9 開始
string get_last_char(const string& s) {
    if (s.length() < 3) return "";
    // 尋找最後一個 UTF-8 字符
    int pos = s.length() - 1;
    while (pos > 0 && (s[pos] & 0xC0) == 0x80) {
        pos--;
    }
    return s.substr(pos);
}

// 取得字串第一個字
string get_first_char(const string& s) {
    if (s.empty()) return "";
    int len = 1;
    if ((s[0] & 0x80) != 0) {
        if ((s[0] & 0xE0) == 0xC0) len = 2;
        else if ((s[0] & 0xF0) == 0xE0) len = 3;
        else if ((s[0] & 0xF8) == 0xF0) len = 4;
    }
    return s.substr(0, len);
}

void dfs(int u) {
    used[u] = true;
    current_path.push_back(u);
    
    if ((int)current_path.size() > max_len) {
        max_len = current_path.size();
        all_max_paths.clear();
        all_max_paths.push_back(current_path);
    } else if ((int)current_path.size() == max_len) {
        all_max_paths.push_back(current_path);
    }
    
    for (int v : adj[u]) {
        if (!used[v]) {
            dfs(v);
        }
    }
    
    current_path.pop_back();
    used[u] = false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> N) {
        idioms.clear();
        for (int i = 0; i <= N; i++) {
            adj[i].clear();
        }
        
        string line;
        getline(cin, line); // consume newline after N
        
        for (int i = 0; i < N; i++) {
            getline(cin, line);
            // Remove potential carriage return
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            idioms.push_back(line);
        }
        
        // Build adjacency list
        for (int i = 0; i < N; i++) {
            string last = get_last_char(idioms[i]);
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                string first = get_first_char(idioms[j]);
                if (last == first) {
                    adj[i].push_back(j);
                }
            }
        }
        
        max_len = 0;
        all_max_paths.clear();
        
        // Try starting from each idiom
        for (int i = 0; i < N; i++) {
            memset(used, 0, sizeof(used));
            current_path.clear();
            dfs(i);
        }
        
        cout << max_len << "\n";
        
        // Output all max paths (problem says if multiple, output all)
        // But looking at sample output, it seems only one path is expected
        // Re-reading: "若長度最長的成語接龍不只一組，則所有串接結果均需列出"
        // However, sample only shows one. Let's check the format again.
        // The sample output format shows only one path.
        // Given typical ZeroJudge problems, they might want all paths printed
        // But the sample doesn't show multiple. Let's assume we print all unique paths.
        // Actually, re-reading carefully: the problem says to list all results if there are multiple.
        // But the sample output format doesn't clarify how to separate them.
        // Looking at similar problems, usually they want all paths printed, each on a new line or something.
        // However, the sample output only has one line for the path.
        // Let me re-read: "輸出最長串接的長度，以及它的內容"
        // And "若長度最長的成語接龍不只一組，則所有串接結果均需列出"
        // This is ambiguous. But given the sample, I'll output all paths, each starting with the format.
        // Wait, actually looking at the problem statement again, it might mean that if there are multiple
        // paths of the same maximum length, we should output all of them.
        // But the sample output format doesn't show how. Let's assume we output each path on a separate line.
        // Actually, let's look at the sample more carefully. The sample input has a unique longest path.
        // For safety, I'll output all max paths, each on a new line after the length.
        // But wait, the problem says "輸出最長串接的長度，以及它的內容" (singular "its content").
        // Then it says if multiple, list all. This is confusing.
        // Let me check typical ZeroJudge e615 solutions behavior.
        // Actually, based on the problem statement structure, I think we should:
        // 1. Print the max length
        // 2. Print each max-length path, one per line (or however makes sense)
        // Since the sample only shows one path, and doesn't show the multi-path case,
        // I'll output each path on a separate line.
        
        // Remove duplicate paths (if any)
        sort(all_max_paths.begin(), all_max_paths.end());
        all_max_paths.erase(unique(all_max_paths.begin(), all_max_paths.end()), all_max_paths.end());
        
        for (const auto& path : all_max_paths) {
            for (int i = 0; i < (int)path.size(); i++) {
                if (i > 0) cout << "→";
                cout << idioms[path[i]];
            }
            cout << "\n";
        }
    }
    
    return 0;
}
