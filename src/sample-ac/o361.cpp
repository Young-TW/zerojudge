#include <iostream>
#include <cstdio>

using namespace std;

void print_int128(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        print_int128(x / 10);
    }
    putchar(x % 10 + '0');
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        __int128 sum = 0;
        long long first_x = 0, first_y = 0;
        long long prev_x = 0, prev_y = 0;
        
        for (int i = 0; i < n; ++i) {
            long long x, y;
            cin >> x >> y;
            if (i == 0) {
                first_x = x;
                first_y = y;
            } else {
                sum += (__int128)prev_x * y - (__int128)x * prev_y;
            }
            prev_x = x;
            prev_y = y;
        }
        
        sum += (__int128)prev_x * first_y - (__int128)first_x * prev_y;
        
        if (sum < 0) {
            sum = -sum;
        }
        
        __int128 area = (sum + 1) / 2;
        print_int128(area);
        putchar('\n');
    }
    
    return 0;
}
