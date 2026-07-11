#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

struct Person {
    string name;
    string father;
    vector<int> path; // Path indices from root
    bool visited;
};

map<string, Person> people;
map<string, vector<string>> children_order;
const string VIRTUAL_ROOT = "__VIRTUAL_ROOT__";

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

string parse_name(string s) {
    s = trim(s);
    while (!s.empty() && (s.back() == ',' || s.back() == '。' || s.back() == '.' || s.back() == ' ')) {
        s.pop_back();
    }
    while (!s.empty() && (s.front() == ' ')) {
        s.erase(0, 1);
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    
    string line;
    getline(cin, line); 

    vector<string> queries(2);

    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        line = trim(line);
        if (line.empty()) continue;

        if (line.find("之父曰") != string::npos) {
            size_t pos = line.find("之父曰");
            string a = parse_name(line.substr(0, pos));
            string b = parse_name(line.substr(pos + 3));
            
            if (people.find(a) == people.end()) {
                people[a] = {a, "", {}, false};
            }
            if (people.find(b) == people.end()) {
                people[b] = {b, "", {}, false};
            }
            people[a].father = b;
        } else if (line.find("之子曰") != string::npos) {
            size_t pos = line.find("之子曰");
            string a = parse_name(line.substr(0, pos));
            string b = parse_name(line.substr(pos + 3));
            
            if (people.find(a) == people.end()) {
                people[a] = {a, "", {}, false};
            }
            if (people.find(b) == people.end()) {
                people[b] = {b, "", {}, false};
            }
            people[b].father = a;
        } else if (line.find("弟") != string::npos && line.find("人") != string::npos) {
            size_t pos_di = line.find("弟");
            size_t pos_ren = line.find("人", pos_di);
            
            string a = parse_name(line.substr(0, pos_di));
            if (people.find(a) == people.end()) {
                people[a] = {a, "", {}, false};
            }
            
            vector<string> bros;
            bros.push_back(a);
            
            string rest = line.substr(pos_ren + 1);
            size_t pos_ci = 0;
            while ((pos_ci = rest.find("次曰")) != string::npos) {
                rest = rest.substr(pos_ci + 2);
                size_t end_pos = rest.find_first_of(",,.");
                if (end_pos == string::npos) end_pos = rest.length();
                
                string name = parse_name(rest.substr(0, end_pos));
                if (people.find(name) == people.end()) {
                    people[name] = {name, "", {}, false};
                }
                bros.push_back(name);
                rest = rest.substr(end_pos);
                if (rest.empty()) break;
            }
            
            string father_name = people[a].father;
            if (father_name == "" || people.find(father_name) == people.end()) {
                father_name = VIRTUAL_ROOT;
            }
            
            for (const string& bro : bros) {
                // 確保兄弟的父親指向正確，如果之前沒設定或設定為空
                if (people[bro].father == "" || people[bro].father == VIRTUAL_ROOT) {
                     if (father_name != VIRTUAL_ROOT) {
                         people[bro].father = father_name;
                     } else {
                         // 如果掛在虛擬根下，父親保持空或設為虛擬根？
                         // 為了 path 計算，設為 VIRTUAL_ROOT 比較好追蹤，但最終輸出不要這個父親。
                         // 這裡我們只在 children_order 中使用 VIRTUAL_ROOT。
                         // people[bro].father 保持空，表示他是根。
                     }
                }
            }
            
            // 將兄弟列表加入 children_order
            // 注意：如果 father_name 是 VIRTUAL_ROOT，我們统一挂在这里
            children_order[father_name].insert(children_order[father_name].end(), bros.begin(), bros.end());
        } else {
            // 可能是查詢行？題目說最後一行是詢問。
            // 但迴圈是 n 行。題目描述：
            // 第一行為 n
            // 接下來 n 行 (定義)
            // 最後一行有一詢問
            // 所以總共是 n+1 行？
            // 範例輸入：
            // 3
            // ... (3 行)
            // 公子光 僚
            // 是的，詢問在第 n+1 行。
            // 所以這個 else 可能不會碰到，或者輸入格式有變體？
            // 題目說 "接下來有 n 行 ... 最後一行有一詢問"。
            // 這通常意味著總共有 n 行定義，然後額外一行詢問。
            // 所以這個 for 迴圈只處理 n 行定義。
            // 詢問在迴圈外讀取。
        }
    }
    
    // 讀取詢問
    string o, p;
    if (!(cin >> o >> p)) return 0;
    
    // 確保查詢的人在 people 中
    if (people.find(o) == people.end()) people[o] = {o, "", {}, false};
    if (people.find(p) == people.end()) people[p] = {p, "", {}, false};
    
    // 如果有未掛載的根節點（沒有父親，也沒在任何兄弟群組中），將它們掛到 VIRTUAL_ROOT
    for (auto& kv : people) {
        if (kv.second.father == "") {
            // 檢查是否已在 children_order[VIRTUAL_ROOT] 中？
            // 簡單的辦法：如果 father 為空，且沒在任何 children_order 的值中出現過（作為孩子）
            // 但我們剛才在處理兄弟時，如果 father 為空，已經加入 children_order[VIRTUAL_ROOT] 了。
            // 這裡處理的是那些單獨的、沒在任何 "弟 m 人" 中出現過的根節點。
            // 將它們加入 VIRTUAL_ROOT 的列表
            // 避免重複加入
            bool found = false;
            for (const auto& child : children_order[VIRTUAL_ROOT]) {
                if (child == kv.first) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                children_order[VIRTUAL_ROOT].push_back(kv.first);
            }
        }
    }
    
    // BFS 計算 path
    // Queue stores name
    vector<string> q;
    
    // 初始化 VIRTUAL_ROOT 的孩子
    if (children_order.find(VIRTUAL_ROOT) != children_order.end()) {
        int idx = 0;
        for (const string& child : children_order[VIRTUAL_ROOT]) {
            if (people.find(child) != people.end()) {
                people[child].path = {idx};
                people[child].visited = true;
                q.push_back(child);
            }
            idx++;
        }
    }
    
    // 還有其他根節點嗎？
    // 如果一個人 father 為空，且不在 children_order[VIRTUAL_ROOT] 中（上面已處理）
    // 那他就是孤立的根？
    // 上面已經把所有 father=="" 的都加入 VIRTUAL_ROOT 了（如果沒在兄弟群組裡）。
    // 在兄弟群組裡的也加入了。
    // 所以所有根節點都應該在 q 中了。
    
    // 等等，如果一個人 father 不為空，但父親還沒處理？
    // BFS 會處理。
    
    // 但是，如果樹的結構是：A 之父曰 B，B 之父曰 C。
    // 我們需要先處理 C，再 B，再 A。
    // 我們的 BFS 從根開始，正好。
    
    // 但我們需要確保所有節點都被訪問。
    // 有些節點可能在 children_order 中作為父親出現，但自己還沒被賦值 path（因為還沒輪到）。
    // BFS 順序：
    // 取出 u。
    // 查找 u 的孩子們 (children_order[u])。
    // 賦予 path = u.path + [index]。
    // 放入 queue。
    
    int head = 0;
    while(head < q.size()){
        string u_name = q[head++];
        if (children_order.find(u_name) != children_order.end()) {
            int idx = 0;
            for (const string& v_name : children_order[u_name]) {
                if (people.find(v_name) != people.end() && !people[v_name].visited) {
                    people[v_name].path = people[u_name].path;
                    people[v_name].path.push_back(idx);
                    people[v_name].visited = true;
                    q.push_back(v_name);
                }
                idx++;
            }
        }
    }
    
    // 檢查是否有未訪問的節點？
    // 理論上不應該有，因為所有節點都應連接到 VIRTUAL_ROOT。
    // 如果有孤立節點（father 指向不存在的人，且自己也不是任何人的孩子）？
    // 題目保證可解。
    
    // 比較 o 和 p
    const vector<int>& path_o = people[o].path;
    const vector<int>& path_p = people[p].path;
    
    // 如果 path 為空？說明沒連上根。
    // 假設不會發生。
    
    // 比較規則：
    // 1. path 長度短者，輩分大，優先。
    // 2. 長度相同，逐位比較，小者優先。
    
    string winner = "";
    if (path_o.size() < path_p.size()) {
        winner = o;
    } else if (path_p.size() < path_o.size()) {
        winner = p;
    } else {
        for (size_t i = 0; i < path_o.size(); ++i) {
            if (path_o[i] < path_p[i]) {
                winner = o;
                break;
            } else if (path_p[i] < path_o[i]) {
                winner = p;
                break;
            }
        }
        // 如果完全相同？題目保證不會有兩者為同輩且祖父不同，且名字不同。
        // 如果路徑完全相同，那是同一個人？題目問 o, p 誰前，暗示不同人。
        // 如果真的是同一人（輸入錯誤？），隨便輸出一個。
        if (winner == "") winner = o; 
    }
    
    cout << winner << endl;

    return 0;
}
