#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N;
    while (cin >> N) {
        vector<long long> factors;
        for (long long i = 1; i * i <= N; ++i) {
            if (N % i == 0) {
                factors.push_back(i);
                if (i * i != N) {
                    factors.push_back(N / i);
                }
            }
        }
        sort(factors.begin(), factors.end());
        for (size_t i = 0; i < factors.size(); ++i) {
            if (i > 0) {
                cout << " ";
            }
            cout << factors[i];
        }
        cout << "\n";
    }
    
    return 0;
}
