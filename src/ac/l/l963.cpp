#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <array>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int H;
    while (cin >> H) {
        int rows, cols;
        cin >> rows >> cols;
        int T;
        cin >> T;
        
        unordered_map<string, int> name_to_id;
        vector<string> id_to_name;
        vector<array<int, 4>> adj; // 0:up, 1:down, 2:left, 3:right
        
        auto get_id = [&](const string& name) -> int {
            auto it = name_to_id.find(name);
            if (it != name_to_id.end()) return it->second;
            int id = id_to_name.size();
            name_to_id[name] = id;
            id_to_name.push_back(name);
            adj.push_back({-1, -1, -1, -1});
            return id;
        };
        
        for (int i = 0; i < T; ++i) {
            string A, dir_str, B;
            cin >> A >> dir_str >> B;
            int idA = get_id(A);
            int idB = get_id(B);
            int dir;
            if (dir_str == "up") dir = 0;
            else if (dir_str == "down") dir = 1;
            else if (dir_str == "left") dir = 2;
            else if (dir_str == "right") dir = 3;
            else continue;
            int opp = (dir == 0) ? 1 : (dir == 1) ? 0 : (dir == 2) ? 3 : 2;
            adj[idA][dir] = idB;
            adj[idB][opp] = idA;
        }
        
        string start_name, q_dir_str;
        int X;
        cin >> start_name >> q_dir_str >> X;
        
        int q_dir;
        if (q_dir_str == "up") q_dir = 0;
        else if (q_dir_str == "down") q_dir = 1;
        else if (q_dir_str == "left") q_dir = 2;
        else if (q_dir_str == "right") q_dir = 3;
        else q_dir = -1;
        
        int current = -1;
        auto it = name_to_id.find(start_name);
        if (it != name_to_id.end()) {
            current = it->second;
        }
        
        for (int i = 0; i < X && current != -1; ++i) {
            current = adj[current][q_dir];
        }
        
        if (current != -1) {
            cout << id_to_name[current] << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
    
    return 0;
}
