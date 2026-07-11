#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    
    int start_x = -1, start_y = -1;
    for (int i = 0; i < T; i++) {
        for (int j = 0; j < T; j++) {
            string cell;
            cin >> cell;
            if (cell == "x") {
                start_x = j + 1;
                start_y = i + 1;
            }
        }
    }
    
    // consume the newline after the grid
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    map<string, pair<int,int>> dirMap;
    dirMap["up"] = {0, -1};
    dirMap["down"] = {0, 1};
    dirMap["left"] = {-1, 0};
    dirMap["right"] = {1, 0};
    dirMap["left up oblique"] = {-1, -1};
    dirMap["right up oblique"] = {1, -1};
    dirMap["left down oblique"] = {-1, 1};
    dirMap["right down oblique"] = {1, 1};
    dirMap["left oblique"] = {-1, -1};
    dirMap["right oblique"] = {1, -1};
    
    int cur_x = start_x;
    int cur_y = start_y;
    
    long long total_exec = 0;
    long long success_exec = 0;
    long long fail_exec = 0;
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        vector<string> tokens;
        stringstream ss(line);
        string tok;
        while (ss >> tok) {
            tokens.push_back(tok);
        }
        if (tokens.empty()) continue;
        
        int steps = stoi(tokens.back());
        tokens.pop_back();
        
        string dir;
        for (size_t i = 0; i < tokens.size(); i++) {
            if (i > 0) dir += " ";
            dir += tokens[i];
        }
        
        auto it = dirMap.find(dir);
        if (it == dirMap.end()) continue; // invalid direction, skip
        
        int dx = it->second.first;
        int dy = it->second.second;
        
        int valid_steps = 0;
        int next_x = cur_x;
        int next_y = cur_y;
        for (int s = 0; s < steps; s++) {
            int nx = next_x + dx;
            int ny = next_y + dy;
            if (nx >= 1 && nx <= T && ny >= 1 && ny <= T) {
                next_x = nx;
                next_y = ny;
                valid_steps++;
            } else {
                break;
            }
        }
        
        if (valid_steps == steps) {
            // fully executed
            total_exec++;
            success_exec++;
            cur_x = next_x;
            cur_y = next_y;
            cout << "x" << cur_x << " y" << cur_y << "\n";
        } else {
            // partially executed or not at all
            if (valid_steps == 0) {
                // cannot execute at all
                total_exec++;
                fail_exec++;
                cout << "-1\n";
            } else {
                // at least one valid step
                if (valid_steps > 1) {
                    // successful execution for the first valid_steps-1 steps
                    total_exec++;
                    success_exec++;
                    int sx = next_x - dx;
                    int sy = next_y - dy;
                    cout << "x" << sx << " y" << sy << "\n";
                }
                // failed execution for the last valid step
                total_exec++;
                fail_exec++;
                cout << "x" << next_x << " y" << next_y << "\n";
                cur_x = next_x;
                cur_y = next_y;
            }
        }
    }
    
    // final coordinate
    cout << "最終坐標為x" << cur_x << " y" << cur_y << "\n";
    
    // percentage
    if (total_exec == 0) {
        cout << "0/0/0/0%\n";
    } else {
        double p = success_exec * 100.0 / total_exec;
        int p10 = (int)round(p * 10);
        if (p10 % 10 == 0) {
            cout << total_exec << "/" << success_exec << "/" << fail_exec << "/" << (p10 / 10) << "%\n";
        } else {
            cout << total_exec << "/" << success_exec << "/" << fail_exec << "/" << (p10 / 10) << "." << (p10 % 10) << "%\n";
        }
    }
    
    return 0;
}
