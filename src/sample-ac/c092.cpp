#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    int map_num = 1;
    const double sq2 = sqrt(2.0) / 2.0;
    
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line == "END") break;
        
        double x = 0.0, y = 0.0;
        stringstream ss(line);
        string token;
        
        while (getline(ss, token, ',')) {
            if (token.empty()) continue;
            if (token.back() == '.') {
                token.pop_back();
            }
            if (token.empty()) continue;
            
            int num = 0;
            int i = 0;
            while (i < (int)token.size() && isdigit(token[i])) {
                num = num * 10 + (token[i] - '0');
                i++;
            }
            string dir = token.substr(i);
            
            if (dir == "N") {
                y += num;
            } else if (dir == "S") {
                y -= num;
            } else if (dir == "E") {
                x += num;
            } else if (dir == "W") {
                x -= num;
            } else if (dir == "NE") {
                x += num * sq2;
                y += num * sq2;
            } else if (dir == "NW") {
                x -= num * sq2;
                y += num * sq2;
            } else if (dir == "SE") {
                x += num * sq2;
                y -= num * sq2;
            } else if (dir == "SW") {
                x -= num * sq2;
                y -= num * sq2;
            }
        }
        
        double dist = sqrt(x * x + y * y);
        cout << "Map #" << map_num << "\n";
        cout << fixed << setprecision(3);
        cout << "The treasure is located at (" << x << "," << y << ").\n";
        cout << "The distance to the treasure is " << dist << ".\n\n";
        map_num++;
    }
    
    return 0;
}
