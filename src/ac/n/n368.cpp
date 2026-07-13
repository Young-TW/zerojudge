#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<long long> vals(N);
        for (int i = 0; i < N; i++) {
            long long a, b;
            cin >> a >> b;
            vals[i] = max(0LL, max(a, b));
        }
        sort(vals.begin(), vals.end(), greater<long long>());
        
        long long sum = 0;
        for (int i = 0; i < N; i++) {
            sum += vals[i];
            cout << sum << "\n";
        }
    }
    
    return 0;
}
