#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef unsigned long long ull;

const ull BASE = 1000000000000000000ULL; // 1e18

void multiply_by_2(vector<ull>& num) {
    ull carry = 0;
    for (size_t i = 0; i < num.size(); ++i) {
        ull cur = num[i] * 2 + carry;
        num[i] = cur % BASE;
        carry = cur / BASE;
    }
    if (carry) {
        num.push_back(carry);
    }
}

void add_factor_times(vector<ull>& a, const vector<ull>& b, ull factor) {
    ull carry = 0;
    size_t n = max(a.size(), b.size());
    if (a.size() < n) a.resize(n, 0);
    
    for (size_t i = 0; i < n; ++i) {
        ull val_b = (i < b.size()) ? b[i] : 0;
        ull prod = val_b * factor + carry;
        ull sum = a[i] + prod;
        
        // Check for overflow in sum? 
        // a[i] < BASE, prod <= 9*BASE + carry_prev. 
        // Max prod approx 9e18 + 9. 
        // Max sum approx 1e18 + 9e18 + 9 = 1e19 + 9 < 1.8e19. Safe.
        
        a[i] = sum % BASE;
        carry = sum / BASE;
        
        // Wait, the logic above is slightly wrong.
        // We are doing a[i] = a[i] + factor * b[i] + carry.
        // Let's redo carefully.
        // cur = a[i] + factor * b[i] + carry.
        // a[i] = cur % BASE.
        // carry = cur / BASE.
        // Max cur = (BASE-1) + 9*(BASE-1) + carry_in.
        // carry_in max is around 9 (from previous step? No).
        // Let's trace carry.
        // cur = a[i] + factor*b[i] + carry.
        // max a[i] = BASE-1.
        // max factor*b[i] = 9*(BASE-1).
        // max carry from prev? 
        // cur_max = BASE-1 + 9*BASE - 9 + carry_in.
        // If carry_in is small, say < 10.
        // cur_max ≈ 10*BASE.
        // carry_out = cur_max / BASE ≈ 10.
        // So carry can be around 10.
        // Then next cur = BASE-1 + 9*BASE - 9 + 10 ≈ 10*BASE.
        // So it's stable.
        // And 10*BASE = 1e19 < 1.8e19. Safe.
    }
    while (carry) {
        a.push_back(carry % BASE);
        carry /= BASE;
    }
}

void divide_by_5(vector<ull>& num) {
    ull remainder = 0;
    for (int i = (int)num.size() - 1; i >= 0; --i) {
        ull cur = remainder * BASE + num[i];
        num[i] = cur / 5;
        remainder = cur % 5;
    }
    // Remove leading zeros
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        int n;
        cin >> n;

        vector<int> result_digits;
        result_digits.reserve(n);

        vector<ull> A;
        A.push_back(0); // A = 0

        vector<ull> P2;
        P2.push_back(1); // P2 = 1 (2^0)

        const int odds[] = {1, 3, 5, 7, 9};

        for (int k = 0; k < n; ++k) {
            // Find d such that (A + d * P2) % 5 == 0
            // Equivalent to (A[0] + d * P2[0]) % 5 == 0
            ull a_mod5 = A[0] % 5;
            ull p2_mod5 = P2[0] % 5;
            
            int d = -1;
            for (int i = 0; i < 5; ++i) {
                if ((a_mod5 + (ull)odds[i] * p2_mod5) % 5 == 0) {
                    d = odds[i];
                    break;
                }
            }
            
            result_digits.push_back(d);

            // A = A + d * P2
            add_factor_times(A, P2, (ull)d);

            // A = A / 5
            divide_by_5(A);

            // P2 = P2 * 2
            multiply_by_2(P2);
        }

        // Output result in reverse order
        for (int i = n - 1; i >= 0; --i) {
            cout << result_digits[i];
        }
        cout << "\n";
    }

    return 0;
}
