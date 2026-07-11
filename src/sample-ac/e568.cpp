#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        for (int i = 1; i <= N; ++i) {
            int x1_1, y1_1, x2_1, y2_1;
            int x1_2, y1_2, x2_2, y2_2;
            cin >> x1_1 >> y1_1 >> x2_1 >> y2_1;
            cin >> x1_2 >> y1_2 >> x2_2 >> y2_2;
            
            int area1 = (x2_1 - x1_1) * (y2_1 - y1_1);
            int area2 = (x2_2 - x1_2) * (y2_2 - y1_2);
            
            int ix1 = max(x1_1, x1_2);
            int iy1 = max(y1_1, y1_2);
            int ix2 = min(x2_1, x2_2);
            int iy2 = min(y2_1, y2_2);
            
            int inter_w = max(0, ix2 - ix1);
            int inter_h = max(0, iy2 - iy1);
            int inter_area = inter_w * inter_h;
            
            int union_area = area1 + area2 - inter_area;
            
            int strong = inter_area;
            int weak = union_area - inter_area;
            int unsafe = 10000 - union_area;
            
            cout << "Night " << i << ": " << strong << " " << weak << " " << unsafe << "\n";
        }
    }
    return 0;
}
