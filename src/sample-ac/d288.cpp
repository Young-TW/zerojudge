#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

void print_fraction(vector<long long> nums, vector<long long> dens) {
    for (size_t i = 0; i < nums.size(); ++i) {
        for (size_t j = 0; j < dens.size(); ++j) {
            long long g = gcd(nums[i], dens[j]);
            if (g > 1) {
                nums[i] /= g;
                dens[j] /= g;
            }
        }
    }
    long long num = 1;
    for (long long x : nums) num *= x;
    long long den = 1;
    for (long long x : dens) den *= x;
    
    long long g = gcd(num, den);
    num /= g;
    den /= g;
    
    if (den == 1) {
        cout << num << "\n";
    } else {
        cout << num << " / " << den << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long k, a, b;
    while (cin >> k >> a >> b) {
        long long a_plus_b = a + b;
        long long two_a_plus_b = 2 * a + b;
        
        // S_AOE = k * a * a / (2 * (a+b) * (2a+b))
        print_fraction({k, a, a}, {2, a_plus_b, two_a_plus_b});
        
        // S_EOC = k * a / (2 * (2a+b))
        print_fraction({k, a}, {2, two_a_plus_b});
        
        // S_COB = k * (a+b) / (2 * (2a+b))
        print_fraction({k, a_plus_b}, {2, two_a_plus_b});
    }
    
    return 0;
}
