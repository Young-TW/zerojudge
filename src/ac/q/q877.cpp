#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cstdint>
#include <sstream>
#include <set>
using namespace std;

bool is_cjk(uint32_t cp) {
    return (cp >= 0x4E00 && cp <= 0x9FFF) ||
           (cp >= 0x3400 && cp <= 0x4DBF) ||
           (cp >= 0xF900 && cp <= 0xFAFF);
}

string filter_cjk(const string& s) {
    string res;
    size_t i = 0;
    while (i < s.size()) {
        unsigned char c = s[i];
        if (c < 0x80) { ++i; continue; }
        if ((c & 0xE0) == 0xC0) { i += 2; continue; }
        if ((c & 0xF0) == 0xE0) {
            if (i + 2 < s.size()) {
                uint32_t cp = ((c & 0x0F) << 12) | ((s[i+1] & 0x3F) << 6) | (s[i+2] & 0x3F);
                if (is_cjk(cp)) res += s.substr(i, 3);
            }
            i += 3;
            continue;
        }
        if ((c & 0xF8) == 0xF0) { i += 4; continue; }
        ++i;
    }
    return res;
}

vector<string> extract_cjk_words(const string& s) {
    vector<string> words;
    size_t i = 0;
    while (i < s.size()) {
        while (i < s.size()) {
            unsigned char c = s[i];
            if (c < 0x80) { ++i; continue; }
            if ((c & 0xE0) == 0xC0) { i += 2; continue; }
            if ((c & 0xF0) == 0xE0) {
                if (i + 2 < s.size()) {
                    uint32_t cp = ((c & 0x0F) << 12) | ((s[i+1] & 0x3F) << 6) | (s[i+2] & 0x3F);
                    if (is_cjk(cp)) break;
                }
                i += 3;
                continue;
            }
            if ((c & 0xF8) == 0xF0) { i += 4; continue; }
            ++i;
        }
        if (i >= s.size()) break;
        string word;
        while (i < s.size()) {
            unsigned char c = s[i];
            if (c < 0x80) break;
            if ((c & 0xE0) == 0xC0) break;
            if ((c & 0xF0) == 0xE0) {
                if (i + 2 < s.size()) {
                    uint32_t cp = ((c & 0x0F) << 12) | ((s[i+1] & 0x3F) << 6) | (s[i+2] & 0x3F);
                    if (is_cjk(cp)) {
                        word += s.substr(i, 3);
                        i += 3;
                        continue;
                    }
                }
                break;
            }
            if ((c & 0xF8) == 0xF0) break;
            break;
        }
        if (!word.empty()) words.push_back(word);
    }
    return words;
}

int main() {
    int n;
    while (cin >> n) {
        cin.ignore(1000, '\n');
        map<string, string> parent;
        vector<pair<string, vector<string>>> pending_brothers;
        set<string> all_names;

        for (int i = 0; i < n; ++i) {
            string line;
            getline(cin, line);
            if (line.empty()) { --i; continue; }

            if (line.find("之父曰") != string::npos) {
                size_t pos = line.find("之父曰");
                string a = filter_cjk(line.substr(0, pos));
                string b = filter_cjk(line.substr(pos + 9));
                if (!a.empty() && !b.empty()) {
                    parent[a] = b;
                    all_names.insert(a);
                    all_names.insert(b);
                }
            } else if (line.find("之子曰") != string::npos) {
                size_t pos = line.find("之子曰");
                string a = filter_cjk(line.substr(0, pos));
                string b = filter_cjk(line.substr(pos + 9));
                if (!a.empty() && !b.empty()) {
                    parent[b] = a;
                    all_names.insert(a);
                    all_names.insert(b);
                }
            } else if (line.find("弟") != string::npos) {
                size_t pos_di = line.find("弟");
                string a = filter_cjk(line.substr(0, pos_di));
                vector<size_t> ci_pos;
                size_t pos = line.find("次曰");
                while (pos != string::npos) {
                    ci_pos.push_back(pos);
                    pos = line.find("次曰", pos + 1);
                }
                vector<string> brothers;
                for (size_t j = 0; j < ci_pos.size(); ++j) {
                    size_t name_start = ci_pos[j] + 6;
                    size_t name_end = (j + 1 < ci_pos.size()) ? ci_pos[j+1] : line.length();
                    string part = line.substr(name_start, name_end - name_start);
                    string name = filter_cjk(part);
                    if (!name.empty()) brothers.push_back(name);
                }
                pending_brothers.push_back({a, brothers});
                all_names.insert(a);
                for (const auto& bro : brothers) all_names.insert(bro);
            }
        }

        string query_line;
        getline(cin, query_line);
        while (query_line.empty()) getline(cin, query_line);
        vector<string> query_names = extract_cjk_words(query_line);
        string o, p;
        if (query_names.size() >= 2) {
            o = query_names[0];
            p = query_names[1];
        } else {
            stringstream ss(query_line);
            ss >> o >> p;
        }

        vector<pair<string, vector<string>>> brother_info;
        for (const auto& pb : pending_brothers) {
            string a = pb.first;
            vector<string> brothers = pb.second;
            string f;
            if (parent.find(a) != parent.end()) f = parent[a];
            else f = "__root__";
            parent[a] = f;
            for (const auto& bro : brothers) parent[bro] = f;
            vector<string> full;
            full.push_back(a);
            for (const auto& bro : brothers) full.push_back(bro);
            brother_info.push_back({f, full});
        }

        all_names.insert(o);
        all_names.insert(p);
        for (const auto& name : all_names) {
            if (parent.find(name) == parent.end()) parent[name] = "__root__";
        }

        map<string, vector<string>> children;
        for (const auto& bi : brother_info) {
            const string& f = bi.first;
            const vector<string>& bros = bi.second;
            vector<string> old = children[f];
            children[f].clear();
            for (const auto& b : bros) children[f].push_back(b);
            for (const auto& c : old) {
                if (find(bros.begin(), bros.end(), c) == bros.end())
                    children[f].push_back(c);
            }
        }
        for (const auto& pr : parent) {
            const string& child = pr.first;
            const string& f = pr.second;
            if (f == "__root__" && child == "__root__") continue;
            if (f.empty()) continue;
            auto it = children.find(f);
            if (it == children.end()) children[f].push_back(child);
            else {
                auto& sons = it->second;
                if (find(sons.begin(), sons.end(), child) == sons.end())
                    sons.push_back(child);
            }
        }

        map<string, vector<int>> path;
        path["__root__"] = {};
        queue<string> q;
        q.push("__root__");
        while (!q.empty()) {
            string f = q.front(); q.pop();
            auto it = children.find(f);
            if (it != children.end()) {
                const auto& sons = it->second;
                for (size_t i = 0; i < sons.size(); ++i) {
                    string c = sons[i];
                    path[c] = path[f];
                    path[c].push_back(i);
                    q.push(c);
                }
            }
        }

        if (path.find(o) == path.end() || path.find(p) == path.end()) {
            cout << o << endl;
            continue;
        }
        const auto& po = path[o];
        const auto& pp = path[p];
        if (po.size() != pp.size())
            cout << (po.size() < pp.size() ? o : p) << endl;
        else
            cout << (po < pp ? o : p) << endl;
    }
    return 0;
}
