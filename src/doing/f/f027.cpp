#include <iostream>
#include <algorithm>

using namespace std;

bool can_form_triangle(long long a, long long b, long long c) {
    if (a + b <= c) return false;
    if (a + c <= b) return false;
    if (b + c <= a) return false;
    return true;
}

bool can_form_quadrilateral(long long a, long long b, long long c) {
    // 嘗試折斷 a
    if (a > 1) {
        // 將 a 折成 1 和 a-1
        // 四邊形條件：最大邊 < 其餘三邊之和
        // 等價於：2 * max_edge < sum
        long long sides[4] = {1, a - 1, b, c};
        sort(sides, sides + 4);
        if (sides[3] < sides[0] + sides[1] + sides[2]) return true;
    }
    
    // 嘗試折斷 b
    if (b > 1) {
        long long sides[4] = {a, 1, b - 1, c};
        sort(sides, sides + 4);
        if (sides[3] < sides[0] + sides[1] + sides[2]) return true;
    }
    
    // 嘗試折斷 c
    if (c > 1) {
        long long sides[4] = {a, b, 1, c - 1};
        sort(sides, sides + 4);
        if (sides[3] < sides[0] + sides[1] + sides[2]) return true;
    }
    
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            long long a, b, c;
            cin >> a >> b >> c;
            
            if (can_form_triangle(a, b, c)) {
                cout << "3\n";
            } else if (can_form_quadrilateral(a, b, c)) {
                cout << "4\n";
            } else {
                cout << "0\n";
            }
        }
    }
    
    return 0;
}
