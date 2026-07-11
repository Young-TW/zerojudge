#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long H, M, S, D;
    while (cin >> H >> M >> S >> D) {
        long long total_seconds = H * 3600 + M * 60 + S + D * 5400;
        total_seconds = (total_seconds % 129600 + 129600) % 129600;
        
        long long h = total_seconds / 3600;
        long long m = (total_seconds % 3600) / 60;
        long long s = total_seconds % 60;
        
        printf("%lld:%02lld:%02lld\n", h, m, s);
    }
    
    return 0;
}
