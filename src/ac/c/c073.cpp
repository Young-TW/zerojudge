#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<vector<int>> blocks(n);
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) {
            blocks[i].push_back(i);
            pos[i] = i;
        }
        
        string cmd1, cmd2;
        while (cin >> cmd1 && cmd1 != "quit") {
            int a, b;
            cin >> a >> cmd2 >> b;
            
            int pos_a = pos[a];
            int pos_b = pos[b];
            
            if (pos_a == pos_b) continue;
            
            int idx_a = -1;
            for (int i = 0; i < blocks[pos_a].size(); ++i) {
                if (blocks[pos_a][i] == a) {
                    idx_a = i;
                    break;
                }
            }
            
            int idx_b = -1;
            for (int i = 0; i < blocks[pos_b].size(); ++i) {
                if (blocks[pos_b][i] == b) {
                    idx_b = i;
                    break;
                }
            }
            
            vector<int> to_move;
            for (int i = idx_a; i < blocks[pos_a].size(); ++i) {
                to_move.push_back(blocks[pos_a][i]);
            }
            blocks[pos_a].resize(idx_a);
            
            if (cmd1 == "move") {
                for (size_t i = 1; i < to_move.size(); ++i) {
                    int block = to_move[i];
                    blocks[block].push_back(block);
                    pos[block] = block;
                }
                to_move.resize(1);
            }
            
            if (cmd2 == "onto") {
                for (int i = idx_b + 1; i < blocks[pos_b].size(); ++i) {
                    int block = blocks[pos_b][i];
                    blocks[block].push_back(block);
                    pos[block] = block;
                }
                blocks[pos_b].resize(idx_b + 1);
            }
            
            for (size_t i = 0; i < to_move.size(); ++i) {
                int block = to_move[i];
                blocks[pos_b].push_back(block);
                pos[block] = pos_b;
            }
        }
        
        for (int i = 0; i < n; ++i) {
            cout << i << ":";
            for (size_t j = 0; j < blocks[i].size(); ++j) {
                cout << " " << blocks[i][j];
            }
            cout << "\n";
        }
    }
    return 0;
}
