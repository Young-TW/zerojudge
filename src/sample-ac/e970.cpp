#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<int> r(N);
        for (int i = 0; i < N; ++i) {
            cin >> r[i];
        }
        
        int B = r[N - 1];
        long long sum = 0;
        
        for (int i = 1; i <= N; i += B) {
            sum += r[i - 1];
        }
        
        long long M = sum % N;
        if (M == 0) {
            M = N;
        }
        
        cout << M << " " << r[M - 1] << "\n";
    }
    
    return 0;
}
