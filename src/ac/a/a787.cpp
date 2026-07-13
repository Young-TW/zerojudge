#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string name;
    int width, height;
    string command;
    
    while (cin >> name >> width >> height >> command) {
        vector<string> grid(height);
        for (int i = 0; i < height; ++i) {
            cin >> grid[i];
        }
        
        bool flip = false, mirror = false;
        for (char c : command) {
            if (c == 'I') flip = true;
            else if (c == 'R') mirror = true;
        }
        
        if (flip) {
            reverse(grid.begin(), grid.end());
        }
        if (mirror) {
            for (string& row : grid) {
                reverse(row.begin(), row.end());
            }
        }
        
        cout << name << "\n";
        for (const string& row : grid) {
            cout << row << "\n";
        }
    }
    
    return 0;
}
