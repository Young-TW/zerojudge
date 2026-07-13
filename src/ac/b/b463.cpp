#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int table[3][256];

void build_table(int channel, const vector<int>& points) {
    int N = points[0];
    vector<int> X(N), Y(N);
    for (int i = 0; i < N; ++i) {
        X[i] = points[1 + 2 * i];
        Y[i] = points[2 + 2 * i];
    }
    
    for (int x = 0; x <= 255; ++x) {
        if (x <= X[0]) {
            table[channel][x] = max(0, min(255, Y[0]));
        } else if (x >= X[N-1]) {
            table[channel][x] = max(0, min(255, Y[N-1]));
        } else {
            long double p = 0;
            for (int i = 0; i < N; ++i) {
                long double term = Y[i];
                for (int j = 0; j < N; ++j) {
                    if (i != j) {
                        term = term * (long double)(x - X[j]) / (long double)(X[i] - X[j]);
                    }
                }
                p += term;
            }
            int val = (int)roundl(p);
            if (val < 0) val = 0;
            if (val > 255) val = 255;
            table[channel][x] = val;
        }
    }
}

bool read_curve(vector<int>& pts) {
    pts.clear();
    int n;
    if (!(cin >> n)) return false;
    pts.push_back(n);
    for (int i = 0; i < 2 * n; ++i) {
        int v;
        if (!(cin >> v)) return false;
        pts.push_back(v);
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> r_pts, g_pts, b_pts;
    while (read_curve(r_pts) && read_curve(g_pts) && read_curve(b_pts)) {
        build_table(0, r_pts);
        build_table(1, g_pts);
        build_table(2, b_pts);
        
        int W, H;
        if (!(cin >> W >> H)) break;
        cout << W << " " << H << "\n";
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                int r, g, b;
                if (!(cin >> r >> g >> b)) break;
                cout << table[0][r] << " " << table[1][g] << " " << table[2][b];
                if (j == W - 1) cout << "\n";
                else cout << " ";
            }
        }
    }
    return 0;
}
