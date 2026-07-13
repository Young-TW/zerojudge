#include <iostream>
#include <iomanip>

using namespace std;

int solve(int k, int cx, int cy, int x, int y) {
    if (k == 0) return 0;
    
    int dx = x - cx; if (dx < 0) dx = -dx;
    int dy = y - cy; if (dy < 0) dy = -dy;
    
    // 剪枝：如果點到當前正方形中心的距離大於 2k，
    // 則該點不可能在當前正方形或其任何子正方形中。
    if (dx > 2 * k || dy > 2 * k) {
        return 0;
    }
    
    int count = 0;
    // 判斷點是否在當前正方形內
    if (dx <= k && dy <= k) {
        count = 1;
    }
    
    int nk = k / 2;
    if (nk > 0) {
        // 遞迴檢查四個子正方形
        count += solve(nk, cx - k, cy - k, x, y);
        count += solve(nk, cx + k, cy - k, x, y);
        count += solve(nk, cx - k, cy + k, x, y);
        count += solve(nk, cx + k, cy + k, x, y);
    }
    
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int k, x, y;
    while (cin >> k >> x >> y) {
        if (k == 0 && x == 0 && y == 0) break;
        // 最大的正方形中心在 (1024, 1024)
        cout << setw(3) << solve(k, 1024, 1024, x, y) << "\n";
    }
    
    return 0;
}
