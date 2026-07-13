#include <iostream>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int A, B, L;
    while (cin >> A >> B >> L) {
        int best_A = 1, best_B = 1;
        long long min_diff = -1;
        
        for (int a = 1; a <= L; ++a) {
            for (int b = 1; b <= L; ++b) {
                if (gcd(a, b) == 1) {
                    if ((long long)a * B >= (long long)A * b) {
                        long long diff = (long long)a * B - (long long)A * b;
                        if (min_diff == -1 || diff < min_diff) {
                            min_diff = diff;
                            best_A = a;
                            best_B = b;
                        }
                    }
                }
            }
        }
        
        cout << best_A << " " << best_B << "\n";
    }
    
    return 0;
}
