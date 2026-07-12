#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        long long len = 1;
        long long count = 9;
        long long start = 1;
        
        while (n > len * count) {
            n -= len * count;
            len++;
            count *= 10;
            start *= 10;
        }
        
        long long num = start + (n - 1) / len;
        long long digit_idx = (n - 1) % len;
        
        string s = to_string(num);
        cout << s[digit_idx] << '\n';
    }
    
    return 0;
}
