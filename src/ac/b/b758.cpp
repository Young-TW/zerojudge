#include <cstdio>

int main() {
    int x, y;
    std::scanf("%d %d", &x, &y);
    int total = x * 60 + y + 150;
    int h = (total / 60) % 24;
    int m = total % 60;
    std::printf("%02d:%02d\n", h, m);
    return 0;
}

// 牛仔(ㄗˇ)很忙
