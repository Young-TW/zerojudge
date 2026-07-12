#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<string> split_utf8(const string& s) {
    vector<string> res;
    for (size_t i = 0; i < s.size(); ) {
        unsigned char c = s[i];
        size_t len = 1;
        if (c <= 0x7F) len = 1;
        else if ((c & 0xE0) == 0xC0) len = 2;
        else if ((c & 0xF0) == 0xE0) len = 3;
        else if ((c & 0xF8) == 0xF0) len = 4;
        else len = 1;
        if (i + len > s.size()) len = s.size() - i;
        res.push_back(s.substr(i, len));
        i += len;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        vector<string> words(N);
        for (int i = 0; i < N; ++i) {
            cin >> words[i];
        }

        vector<string> first_char(N), last_char(N);
        for (int i = 0; i < N; ++i) {
            vector<string> chars = split_utf8(words[i]);
            first_char[i] = chars.front();
            last_char[i] = chars.back();
        }

        unordered_map<string, int> start_map, end_map;
        for (int i = 0; i < N; ++i) {
            start_map[first_char[i]] = i;
            end_map[last_char[i]] = i;
        }

        vector<int> next(N, -1), prev(N, -1);
        for (int i = 0; i < N; ++i) {
            auto it_next = start_map.find(last_char[i]);
            if (it_next != start_map.end()) next[i] = it_next->second;
            auto it_prev = end_map.find(first_char[i]);
            if (it_prev != end_map.end()) prev[i] = it_prev->second;
        }

        vector<bool> visited(N, false);
        struct Component {
            vector<int> words;
            bool is_cycle;
        };
        vector<Component> components;

        // Paths: start from heads (prev == -1)
        for (int i = 0; i < N; ++i) {
            if (prev[i] == -1 && !visited[i]) {
                Component comp;
                comp.is_cycle = false;
                int cur = i;
                while (cur != -1 && !visited[cur]) {
                    visited[cur] = true;
                    comp.words.push_back(cur);
                    cur = next[cur];
                }
                components.push_back(comp);
            }
        }

        // Cycles: remaining unvisited nodes
        for (int i = 0; i < N; ++i) {
            if (!visited[i]) {
                Component comp;
                comp.is_cycle = true;
                int cur = i;
                while (!visited[cur]) {
                    visited[cur] = true;
                    comp.words.push_back(cur);
                    cur = next[cur];
                }
                components.push_back(comp);
            }
        }

        int max_len = 0;
        for (const auto& comp : components) {
            if (static_cast<int>(comp.words.size()) > max_len) {
                max_len = comp.words.size();
            }
        }

        cout << max_len << '\n';
        if (max_len == 1) {
            cout << "什麼爛表\n";
        } else {
            vector<bool> is_candidate(N, false);
            for (const auto& comp : components) {
                if (static_cast<int>(comp.words.size()) == max_len) {
                    if (comp.is_cycle) {
                        for (int idx : comp.words) is_candidate[idx] = true;
                    } else {
                        is_candidate[comp.words[0]] = true;
                    }
                }
            }
            bool first = true;
            for (int i = 0; i < N; ++i) {
                if (is_candidate[i]) {
                    if (!first) cout << ' ';
                    cout << words[i];
                    first = false;
                }
            }
            cout << '\n';
        }
    }
    return 0;
}
