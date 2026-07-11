#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a;
    while (cin >> a) {
        vector<vector<string>> players(9);
        players[0].resize(a);
        for (int j = 0; j < a; ++j) {
            cin >> players[0][j];
        }
        for (int i = 1; i < 9; ++i) {
            int cnt;
            cin >> cnt;
            players[i].resize(cnt);
            for (int j = 0; j < cnt; ++j) {
                cin >> players[i][j];
            }
        }
        int b;
        cin >> b;
        
        vector<int> bases;
        int score = 0;
        int outs = 0;
        int total_outs = 0;
        vector<int> at_bat_count(9, 0);
        int current_batter = 0;
        
        while (true) {
            if (at_bat_count[current_batter] >= (int)players[current_batter].size()) {
                current_batter = (current_batter + 1) % 9;
                continue;
            }
            
            int idx = at_bat_count[current_batter];
            string res = players[current_batter][idx];
            at_bat_count[current_batter]++;
            current_batter = (current_batter + 1) % 9;

            if (res == "1B" || res == "2B" || res == "3B" || res == "HR") {
                int K = 0;
                if (res == "1B") K = 1;
                else if (res == "2B") K = 2;
                else if (res == "3B") K = 3;
                else if (res == "HR") K = 4;
                
                vector<int> new_bases;
                for (size_t i = 0; i < bases.size(); ++i) {
                    int new_pos = bases[i] + K;
                    if (new_pos >= 4) {
                        score++;
                    } else {
                        new_bases.push_back(new_pos);
                    }
                }
                if (K >= 4) {
                    score++;
                } else {
                    new_bases.push_back(K);
                }
                bases = new_bases;
            } else {
                total_outs++;
                outs++;
                if (outs == 3) {
                    outs = 0;
                    bases.clear();
                }
                if (total_outs == b) {
                    break;
                }
            }
        }
        cout << score << "\n";
    }
    
    return 0;
}
