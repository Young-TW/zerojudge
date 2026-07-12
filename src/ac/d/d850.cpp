#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<int> a(N);
        long long sum = 0;
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
            sum += a[i];
        }
        
        long long avg = sum / N;
        int moves = 0;
        
        for (int i = 0; i < N - 1; ++i) {
            if (a[i] != avg) {
                moves++;
                a[i + 1] += a[i] - avg;
            }
        }
        
        cout << moves << "\n";
    }
    
    return 0;
}
