#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    int T;
    if (!(cin >> T)) return 0;
    
    int cur_x = 0, cur_y = 0;
    for (int i = 1; i <= T; ++i) {
        for (int j = 1; j <= T; ++j) {
            string cell;
            cin >> cell;
            if (cell == "x") {
                cur_x = j;
                cur_y = i;
            }
        }
    }
    
    string dir;
    int steps;
    int total = 0, success = 0, fail = 0;
    
    while (cin >> dir >> steps) {
        total++;
        int nx = cur_x, ny = cur_y;
        if (dir == "right") {
            nx += steps;
        } else if (dir == "left") {
            nx -= steps;
        } else if (dir == "down") {
            ny += steps;
        } else if (dir == "up") {
            ny -= steps;
        }
        
        if (nx >= 1 && nx <= T && ny >= 1 && ny <= T) {
            cur_x = nx;
            cur_y = ny;
            success++;
            cout << "x" << cur_x << " y" << cur_y << "\n";
        } else {
            fail++;
            cout << "-1\n";
        }
    }
    
    cout << "最終坐標為x" << cur_x << " y" << cur_y << "\n";
    
    cout << total << "/" << success << "/" << fail << "/";
    if (total == 0) {
        cout << "0%";
    } else {
        double pct = (double)success * 100.0 / total;
        if (pct == (int)pct) {
            cout << (int)pct << "%";
        } else {
            cout << fixed << setprecision(1) << pct << "%";
        }
    }
    cout << "\n";
    
    return 0;
}
