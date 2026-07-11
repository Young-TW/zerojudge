#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <functional>

using namespace std;

char buf[1 << 16];
int p = 0, len = 0;
inline char getChar() {
    if (p == len) {
        len = fread(buf, 1, sizeof(buf), stdin);
        p = 0;
        if (len == 0) return EOF;
    }
    return buf[p++];
}
inline bool readInt(int &x) {
    char c = getChar();
    while (c != EOF && (c < '0' || c > '9')) c = getChar();
    if (c == EOF) return false;
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getChar();
    }
    return true;
}

int main() {
    int X, Y, Z;
    while (readInt(X) && readInt(Y) && readInt(Z)) {
        int Y1 = Y + 1, Z1 = Z + 1;
        int total_size = (X + 1) * Y1 * Z1;
        vector<int> P(total_size, 0);
        
        for (int x = 1; x <= X; ++x) {
            int base_x = x * Y1 * Z1;
            int base_xm = (x - 1) * Y1 * Z1;
            for (int y = 1; y <= Y; ++y) {
                int base_xy = base_x + y * Z1;
                int base_xym = base_x + (y - 1) * Z1;
                int base_xm_y = base_xm + y * Z1;
                int base_xm_ym = base_xm + (y - 1) * Z1;
                for (int z = 1; z <= Z; ++z) {
                    int val;
                    readInt(val);
                    P[base_xy + z] = val
                        + P[base_xm_y + z]
                        + P[base_xym + z]
                        + P[base_xy + z - 1]
                        - P[base_xm_ym + z]
                        - P[base_xm_y + z - 1]
                        - P[base_xym + z - 1]
                        + P[base_xm_ym + z - 1];
                }
            }
        }
        
        int T;
        readInt(T);
        while (T--) {
            int x1, y1, z1, x2, y2, z2;
            readInt(x1); readInt(y1); readInt(z1);
            readInt(x2); readInt(y2); readInt(z2);
            
            int base_x2 = x2 * Y1 * Z1;
            int base_x1m = (x1 - 1) * Y1 * Z1;
            
            int base_x2_y2 = base_x2 + y2 * Z1;
            int base_x2_y1m = base_x2 + (y1 - 1) * Z1;
            int base_x1m_y2 = base_x1m + y2 * Z1;
            int base_x1m_y1m = base_x1m + (y1 - 1) * Z1;
            
            int ans = P[base_x2_y2 + z2]
                - P[base_x1m_y2 + z2]
                - P[base_x2_y1m + z2]
                - P[base_x2_y2 + z1 - 1]
                + P[base_x1m_y1m + z2]
                + P[base_x1m_y2 + z1 - 1]
                + P[base_x2_y1m + z1 - 1]
                - P[base_x1m_y1m + z1 - 1];
                
            printf("%d\n", ans);
        }
    }
    return 0;
}
