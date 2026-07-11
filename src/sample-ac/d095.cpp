#include <cstdio>

int main() {
    int h, m;
    while (scanf("%d:%d", &h, &m) == 2) {
        if (h == 0 && m == 0) break;
        double angle = (h % 12) * 30.0 - m * 5.5;
        if (angle < 0) angle = -angle;
        if (angle > 180.0) {
            angle = 360.0 - angle;
        }
        printf("%.3f\n", angle);
    }
    return 0;
}
