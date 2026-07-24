#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

struct Pixel {
    int r, g, b, a;
};

inline int clamp255(int v) {
    if (v < 0) return 0;
    if (v > 255) return 255;
    return v;
}

// nearest integer with tie‑breaking: left/up preferred
inline int nearest_int(double x, int max_idx) {
    int low = (int)std::floor(x);
    int high = low + 1;
    double dLow = x - low;
    double dHigh = high - x;
    int chosen;
    if (high > max_idx) {
        chosen = low;
    } else if (low < 0) {
        chosen = high;
    } else {
        if (dLow <= dHigh) chosen = low;
        else chosen = high;
    }
    if (chosen < 0) chosen = 0;
    if (chosen > max_idx) chosen = max_idx;
    return chosen;
}

// linear interpolation between two integer values
inline double lerp(double a, double b, double t) {
    return a * (1.0 - t) + b * t;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    double SX, SY;
    int TYPE;
    if (!(std::cin >> SX >> SY >> TYPE)) return 0;
    
    int W, H;
    std::cin >> W >> H;
    std::vector<std::vector<Pixel>> img(H, std::vector<Pixel>(W));
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            int r, g, b, a;
            std::cin >> r >> g >> b >> a;
            img[y][x] = {r, g, b, a};
        }
    }
    
    // validation
    bool keep_original = false;
    if (SX <= 0 || SY <= 0) keep_original = true;
    if (TYPE != 0 && TYPE != 1) keep_original = true;
    
    int nW = (int)std::round(W * SX);
    int nH = (int)std::round(H * SY);
    if (nW <= 0 || nH <= 0 || nW > 256 || nH > 256) keep_original = true;
    
    if (keep_original) {
        std::cout << W << ' ' << H << '\n';
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                const Pixel &p = img[y][x];
                std::cout << p.r << ' ' << p.g << ' ' << p.b << ' ' << p.a;
                if (x + 1 != W) std::cout << ' ';
            }
            if (y + 1 != H) std::cout << '\n';
        }
        return 0;
    }
    
    // ---------- horizontal pass ----------
    // intermediate image: height H, width nW, store as double per channel
    struct DPixel { double r, g, b, a; };
    std::vector<std::vector<DPixel>> horiz(H, std::vector<DPixel>(nW));
    
    for (int y = 0; y < H; ++y) {
        for (int nx = 0; nx < nW; ++nx) {
            double ox = (SX == 0) ? 0.0 : (static_cast<double>(nx) / SX);
            if (TYPE == 0) { // bilinear (horizontal part)
                int x0 = (int)std::floor(ox);
                int x1 = x0 + 1;
                if (x0 < 0) x0 = 0;
                if (x0 >= W) x0 = W - 1;
                if (x1 < 0) x1 = 0;
                if (x1 >= W) x1 = W - 1;
                double dx = ox - std::floor(ox);
                if (x0 == x1) dx = 0.0; // edge, use single point
                const Pixel &p0 = img[y][x0];
                const Pixel &p1 = img[y][x1];
                horiz[y][nx].r = lerp(p0.r, p1.r, dx);
                horiz[y][nx].g = lerp(p0.g, p1.g, dx);
                horiz[y][nx].b = lerp(p0.b, p1.b, dx);
                horiz[y][nx].a = lerp(p0.a, p1.a, dx);
            } else { // nearest neighbor (horizontal)
                int xi = nearest_int(ox, W - 1);
                const Pixel &p = img[y][xi];
                horiz[y][nx].r = p.r;
                horiz[y][nx].g = p.g;
                horiz[y][nx].b = p.b;
                horiz[y][nx].a = p.a;
            }
        }
    }
    
    // ---------- vertical pass ----------
    std::vector<std::vector<Pixel>> out(nH, std::vector<Pixel>(nW));
    
    for (int ny = 0; ny < nH; ++ny) {
        double oy = (SY == 0) ? 0.0 : (static_cast<double>(ny) / SY);
        for (int nx = 0; nx < nW; ++nx) {
            if (TYPE == 0) { // bilinear (vertical part)
                int y0 = (int)std::floor(oy);
                int y1 = y0 + 1;
                if (y0 < 0) y0 = 0;
                if (y0 >= H) y0 = H - 1;
                if (y1 < 0) y1 = 0;
                if (y1 >= H) y1 = H - 1;
                double dy = oy - std::floor(oy);
                if (y0 == y1) dy = 0.0;
                const DPixel &v0 = horiz[y0][nx];
                const DPixel &v1 = horiz[y1][nx];
                double r = lerp(v0.r, v1.r, dy);
                double g = lerp(v0.g, v1.g, dy);
                double b = lerp(v0.b, v1.b, dy);
                double a = lerp(v0.a, v1.a, dy);
                out[ny][nx].r = clamp255((int)std::round(r));
                out[ny][nx].g = clamp255((int)std::round(g));
                out[ny][nx].b = clamp255((int)std::round(b));
                out[ny][nx].a = clamp255((int)std::round(a));
            } else { // nearest neighbor (vertical)
                int yi = nearest_int(oy, H - 1);
                const DPixel &v = horiz[yi][nx];
                out[ny][nx].r = clamp255((int)std::round(v.r));
                out[ny][nx].g = clamp255((int)std::round(v.g));
                out[ny][nx].b = clamp255((int)std::round(v.b));
                out[ny][nx].a = clamp255((int)std::round(v.a));
            }
        }
    }
    
    // ---------- output ----------
    std::cout << nW << ' ' << nH << '\n';
    for (int y = 0; y < nH; ++y) {
        for (int x = 0; x < nW; ++x) {
            const Pixel &p = out[y][x];
            std::cout << p.r << ' ' << p.g << ' ' << p.b << ' ' << p.a;
            if (x + 1 != nW) std::cout << ' ';
        }
        if (y + 1 != nH) std::cout << '\n';
    }
    return 0;
}
