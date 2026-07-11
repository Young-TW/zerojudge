#include <cstdio>
#include <cmath>

int main() {
    int W, H, TYPE;
    int R1, G1, B1, A1, R2, G2, B2, A2;
    while (scanf("%d %d %d %d %d %d %d %d %d %d %d", &W, &H, &TYPE, &R1, &G1, &B1, &A1, &R2, &G2, &B2, &A2) == 11) {
        printf("%d %d\n", W, H);
        if (TYPE == 0) {
            for (int y = 0; y < H; ++y) {
                for (int x = 0; x < W; ++x) {
                    double t = (W == 1) ? 0.0 : (double)x / (W - 1);
                    int r = (int)round(R1 + (R2 - R1) * t);
                    int g = (int)round(G1 + (G2 - G1) * t);
                    int b = (int)round(B1 + (B2 - B1) * t);
                    int a = (int)round(A1 + (A2 - A1) * t);
                    if (x == W - 1) printf("%d %d %d %d\n", r, g, b, a);
                    else printf("%d %d %d %d ", r, g, b, a);
                }
            }
        } else {
            double cx = (W - 1) / 2.0;
            double cy = (H - 1) / 2.0;
            double max_d = sqrt(cx * cx + cy * cy);
            for (int y = 0; y < H; ++y) {
                for (int x = 0; x < W; ++x) {
                    double dx = x - cx;
                    double dy = y - cy;
                    double d = sqrt(dx * dx + dy * dy);
                    double t = (max_d == 0.0) ? 0.0 : d / max_d;
                    if (t > 1.0) t = 1.0;
                    int r = (int)round(R1 + (R2 - R1) * t);
                    int g = (int)round(G1 + (G2 - G1) * t);
                    int b = (int)round(B1 + (B2 - B1) * t);
                    int a = (int)round(A1 + (A2 - A1) * t);
                    if (x == W - 1) printf("%d %d %d %d\n", r, g, b, a);
                    else printf("%d %d %d %d ", r, g, b, a);
                }
            }
        }
    }
    return 0;
}
