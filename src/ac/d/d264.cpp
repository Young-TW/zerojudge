#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long k;
    vector<long long> fib;
    fib.push_back(1);
    fib.push_back(1);
    
    while (true) {
        long long next = fib.back() + fib[fib.size() - 2];
        if (next > 2000000000LL) break;
        fib.push_back(next);
    }
    
    while (cin >> k) {
        for (int i = fib.size() - 1; i >= 1; --i) {
            if (fib[i] <= k) {
                cout << fib[i - 1] << " " << fib[i] << "\n";
                break;
            }
        }
    }
    
    return 0;
}
