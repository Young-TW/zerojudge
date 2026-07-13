#include <iostream>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        long long original = n;
        set<long long> seen;
        bool happy = false;
        while (true) {
            if (n == 1) {
                happy = true;
                break;
            }
            if (seen.find(n) != seen.end()) {
                happy = false;
                break;
            }
            seen.insert(n);
            long long sum = 0;
            long long temp = n;
            while (temp > 0) {
                long long d = temp % 10;
                sum += d * d;
                temp /= 10;
            }
            n = sum;
        }
        if (happy) {
            cout << original << " is a happy number\n";
        } else {
            cout << original << " is an unhappy number\n";
        }
    }
    return 0;
}
