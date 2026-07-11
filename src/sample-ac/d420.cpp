#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long A, L;
    int case_num = 1;
    
    while (cin >> A >> L) {
        if (A < 0 && L < 0) {
            break;
        }
        
        long long current_A = A;
        int terms = 1;
        
        while (current_A != 1) {
            if (current_A % 2 == 0) {
                current_A /= 2;
                terms++;
            } else {
                if (3 * current_A + 1 > L) {
                    break;
                }
                current_A = 3 * current_A + 1;
                terms++;
            }
        }
        
        cout << "Case " << case_num << ": A = " << A << ", limit = " << L << ", number of terms = " << terms << "\n";
        case_num++;
    }
    
    return 0;
}
