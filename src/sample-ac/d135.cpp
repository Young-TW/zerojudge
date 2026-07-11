#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

long long readDoubleAsInt() {
    string s;
    if (!(cin >> s)) return 0;
    if (s.empty()) return 0;
    long long val = 0;
    bool neg = false;
    int i = 0;
    if (s[0] == '-') {
        neg = true;
        i++;
    }
    for (; i < s.length() && s[i] != '.'; ++i) {
        val = val * 10 + (s[i] - '0');
    }
    val *= 100;
    if (i < s.length() && s[i] == '.') {
        i++;
        if (i < s.length()) {
            val += (s[i] - '0') * 10;
            i++;
        }
        if (i < s.length()) {
            val += (s[i] - '0');
        }
    }
    return neg ? -val : val;
}

long long cross(long long ax, long long ay, long long bx, long long by, long long cx, long long cy) {
    return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
}

bool pointInTriangle(long long px, long long py, long long ax, long long ay, long long bx, long long by, long long cx, long long cy) {
    long long d1 = cross(ax, ay, bx, by, px, py);
    long long d2 = cross(bx, by, cx, cy, px, py);
    long long d3 = cross(cx, cy, ax, ay, px, py);
    
    bool hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);
    
    if (hasNeg && hasPos) {
        return false;
    }
    
    long long area = cross(ax, ay, bx, by, cx, cy);
    if (area != 0) {
        return true;
    }
    
    long long minX = min({ax, bx, cx});
    long long maxX = max({ax, bx, cx});
    long long minY = min({ay, by, cy});
    long long maxY = max({ay, by, cy});
    return px >= minX && px <= maxX && py >= minY && py <= maxY;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long ax, ay, bx, by, cx, cy;
    while (true) {
        ax = readDoubleAsInt();
        ay = readDoubleAsInt();
        bx = readDoubleAsInt();
        by = readDoubleAsInt();
        cx = readDoubleAsInt();
        cy = readDoubleAsInt();
        
        if (ax == 0 && ay == 0 && bx == 0 && by == 0 && cx == 0 && cy == 0) {
            break;
        }
        
        int count = 0;
        for (int x = 1; x <= 99; ++x) {
            for (int y = 1; y <= 99; ++y) {
                if (pointInTriangle(x * 100, y * 100, ax, ay, bx, by, cx, cy)) {
                    count++;
                }
            }
        }
        cout << setw(4) << count << "\n";
    }
    
    return 0;
}
