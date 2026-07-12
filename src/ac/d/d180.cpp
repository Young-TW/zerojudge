#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        int sum_odd = 0;
        int sum_even = 0;
        for (int i = 0; i < N; ++i) {
            int val;
            cin >> val;
            if (i % 2 == 0) {
                sum_odd += val;
            } else {
                sum_even += val;
            }
        }
        
        if (sum_odd >= sum_even) {
            cout << "left\n";
        } else {
            cout << "right\n";
        }
    }
    
    return 0;
}
