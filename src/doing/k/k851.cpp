#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long k;
    string s;
    while (cin >> k >> s) {
        long long sum = 0;
        for (long long i = 0; i < static_cast<long long>(s.size()); ++i) {
            int digit = s[i] - '0';
            sum = (sum + digit * i) % k;
        }
        if (sum % k == 0) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
