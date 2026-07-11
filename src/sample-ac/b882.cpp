#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    long long H, M, S;
    while (cin >> H >> M >> S) {
        long long total_seconds = H * 3600 + M * 60 + S;
        int hh = (total_seconds / 3600) % 24;
        int mm = (total_seconds / 60) % 60;
        int ss = total_seconds % 60;
        printf("%02d:%02d:%02d\n", hh, mm, ss);
    }
    return 0;
}
