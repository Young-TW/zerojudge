#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n != 0) {
        int top = 1, bottom = 6;
        int north = 2, south = 5;
        int east = 4, west = 3;
        
        for (int i = 0; i < n; ++i) {
            string cmd;
            cin >> cmd;
            
            if (cmd == "north") {
                int tmp = top;
                top = south;
                south = bottom;
                bottom = north;
                north = tmp;
            } else if (cmd == "south") {
                int tmp = top;
                top = north;
                north = bottom;
                bottom = south;
                south = tmp;
            } else if (cmd == "east") {
                int tmp = top;
                top = west;
                west = bottom;
                bottom = east;
                east = tmp;
            } else if (cmd == "west") {
                int tmp = top;
                top = east;
                east = bottom;
                bottom = west;
                west = tmp;
            }
        }
        
        cout << top << "\n";
    }
    
    return 0;
}
