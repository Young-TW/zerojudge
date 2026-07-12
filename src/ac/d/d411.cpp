#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string M;
    int N;
    while (cin >> M >> N) {
        int p2 = 1 << N;
        int take = max(N, 1);
        string sub;
        if (M.length() >= take) {
            sub = M.substr(M.length() - take);
        } else {
            sub = M;
        }
        
        int num = 0;
        for (char c : sub) {
            num = num * 10 + (c - '0');
        }
        
        if (num % p2 == 0) {
            cout << "YA!!終於算出" << M << "可被2的" << N << "次整除了!!\n";
        } else {
            cout << "可惡!!算了這麼久" << M << "竟然無法被2的" << N << "次整除\n";
        }
    }
    
    return 0;
}
