#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    bool first_case = true;
    while (cin >> N && N) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;
        
        bool found = false;
        for (int fghijk = 1; fghijk * N <= 98765; ++fghijk) {
            int abcde = fghijk * N;
            int mask = 0;
            int temp = fghijk;
            for (int i = 0; i < 5; ++i) {
                mask |= (1 << (temp % 10));
                temp /= 10;
            }
            temp = abcde;
            for (int i = 0; i < 5; ++i) {
                mask |= (1 << (temp % 10));
                temp /= 10;
            }
            if (mask == (1 << 10) - 1) {
                cout << setfill('0') << setw(5) << abcde << " / " << setfill('0') << setw(5) << fghijk << " = " << N << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "There are no solutions for " << N << ".\n";
        }
    }
    return 0;
}
