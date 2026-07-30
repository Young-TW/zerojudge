#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int T;
    while (cin >> T) {
        while (T--) {
            int h, m;
            char c;
            cin >> h >> c >> m;
            if (h == 12) h = 0;
            int total = h * 60 + m;
            int real_total = (720 - total) % 720;
            int real_h = real_total / 60;
            int real_m = real_total % 60;
            if (real_h == 0) real_h = 12;
            printf("%02d:%02d\n", real_h, real_m);
        }
    }
    return 0;
}
