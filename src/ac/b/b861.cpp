#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    if (!getline(cin, line)) return 0;
    int T = stoi(line);
    
    while (T--) {
        getline(cin, line);
        stringstream ss(line);
        string action;
        int C = 0, T_count = 0;
        bool cond2 = false;
        
        while (ss >> action) {
            if (action == "chi") {
                C++;
            } else if (action == "tu") {
                T_count++;
            }
            if (T_count > C) {
                cond2 = true;
            }
        }
        
        bool cond1 = (C > T_count);
        
        if (cond1 && cond2) {
            cout << "chi pu tao bu tu pu tao pi, bu chi pu tao dao tu pu tao pi\n";
        } else if (cond1) {
            cout << "chi pu tao bu tu pu tao pi\n";
        } else if (cond2) {
            cout << "bu chi pu tao dao tu pu tao pi\n";
        } else {
            cout << "chi pu tao tu pu tao pi\n";
        }
    }
    
    return 0;
}
