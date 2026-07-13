#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    double sums[1000];
    sums[0] = 0.0;
    int max_n = 0;
    double current_sum = 0.0;
    for (int i = 1; i < 1000; ++i) {
        current_sum += 1.0 / (i + 1);
        sums[i] = current_sum;
        if (current_sum > 5.20) {
            max_n = i;
            break;
        }
    }
    
    double c;
    while (cin >> c) {
        for (int i = 1; i <= max_n; ++i) {
            if (sums[i] >= c) {
                cout << i << " card(s)\n";
                break;
            }
        }
    }
    
    return 0;
}
