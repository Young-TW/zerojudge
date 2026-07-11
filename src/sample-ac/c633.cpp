#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

unsigned long long sum_of_prime_factors(unsigned long long n) {
    if (n <= 1) return 0;
    unsigned long long sum = 0;
    if (n % 2 == 0) {
        sum += 2;
        while (n % 2 == 0) {
            n /= 2;
        }
    }
    for (unsigned long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        sum += n;
    }
    return sum;
}

struct Data {
    string S;
    string T;
    unsigned long long N;
    unsigned long long sum;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<Data> v;
    string s;
    while (cin >> s) {
        Data d;
        d.S = s;
        string num_str;
        for (char c : s) {
            unsigned char uc = c;
            if (isalpha(uc)) {
                d.T += c;
            } else if (isdigit(uc)) {
                num_str += c;
            }
        }
        if (num_str.empty()) {
            d.N = 0;
        } else {
            try {
                d.N = stoull(num_str);
            } catch (...) {
                d.N = 0;
            }
        }
        d.sum = sum_of_prime_factors(d.N);
        v.push_back(d);
    }
    
    sort(v.begin(), v.end(), [](const Data& a, const Data& b) {
        if (a.sum != b.sum) return a.sum > b.sum;
        if (a.T != b.T) return a.T < b.T;
        return a.N > b.N;
    });
    
    for (const auto& d : v) {
        cout << d.S << "\n";
    }
    
    return 0;
}
