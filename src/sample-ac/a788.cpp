#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

int main() {
    double x1_start, y1_start, x1_end, y1_end;
    double x2_start, y2_start, x2_end, y2_end;
    
    while (cin >> x1_start >> y1_start >> x1_end >> y1_end >> x2_start >> y2_start >> x2_end >> y2_end) {
        if (x1_start == 0 && y1_start == 0 && x1_end == 0 && y1_end == 0 && 
            x2_start == 0 && y2_start == 0 && x2_end == 0 && y2_end == 0) {
            break;
        }
        
        double start_mid_x = (x1_start + x2_start) / 2.0;
        double start_mid_y = (y1_start + y2_start) / 2.0;
        double end_mid_x = (x1_end + x2_end) / 2.0;
        double end_mid_y = (y1_end + y2_end) / 2.0;
        
        double dx = end_mid_x - start_mid_x;
        double dy = end_mid_y - start_mid_y;
        
        double d_start_sq = (x2_start - x1_start) * (x2_start - x1_start) + (y2_start - y1_start) * (y2_start - y1_start);
        double d_end_sq = (x2_end - x1_end) * (x2_end - x1_end) + (y2_end - y1_end) * (y2_end - y1_end);
        
        double scale = sqrt(d_end_sq / d_start_sq);
        
        double m1 = (y2_start - y1_start) / (x2_start - x1_start);
        double m2 = (y2_end - y1_end) / (x2_end - x1_end);
        
        double angle = atan2(m2 - m1, 1 + m1 * m2);
        
        printf("%d %d %.3f %.3f\n", (int)floor(dx + 1e-9), (int)floor(dy + 1e-9), scale + 1e-9, angle + 1e-9);
    }
    return 0;
}
