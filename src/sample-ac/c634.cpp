#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long sum_of_prime_factors(long long n) {
    if (n <= 1) return 0;
    long long sum = 0;
    if (n % 2 == 0) {
        sum += 2;
        while (n % 2 == 0) n /= 2;
    }
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) sum += n;
    return sum;
}

struct Data {
    long long spf;
    string T;
    long long N;
    string S;
};

bool cmp(const Data& a, const Data& b) {
    if (a.spf != b.spf) return a.spf > b.spf;
    if (a.T != b.T) return a.T < b.T;
    return a.N > b.N;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string S;
    vector<Data> v;
    while (cin >> S) {
        string T = "";
        string num_str = "";
        for (char c : S) {
            if (c >= '0' && c <= '9') {
                num_str += c;
            } else {
                T += c;
            }
        }
        long long N = 0;
        for (char c : num_str) {
            N = N * 10 + (c - '0');
        }
        long long spf = sum_of_prime_factors(N);
        v.push_back({spf, T, N, S});
    }
    
    sort(v.begin(), v.end(), cmp);
    
    for (const auto& d : v) {
        cout << d.S << "\n";
    }
    
    return 0;
}
