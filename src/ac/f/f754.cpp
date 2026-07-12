#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;
    
    for (int c = 1; c <= N; c++) {
        long long M, K;
        cin >> M >> K;
        
        cout << "Case " << c << " :\n";
        
        long long base = M / K;
        long long rem = M % K;
        
        for (long long i = 1; i <= K; i++) {
            long long amount = base;
            if (i == K) amount += rem;
            cout << "第" << i << "位 : 拿" << amount << "元並說DD! BAD!\n";
        }
    }
    
    return 0;
}
