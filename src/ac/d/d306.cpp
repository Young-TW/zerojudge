#include <iostream>
#include <string>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long strToLongLong(const string& s) {
    long long res = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        res = res * 2 + (s[i] - '0');
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        for (int i = 1; i <= N; ++i) {
            string s1, s2;
            cin >> s1 >> s2;
            
            long long n1 = strToLongLong(s1);
            long long n2 = strToLongLong(s2);
            
            long long g = gcd(n1, n2);
            
            if (g >= 2) {
                cout << "Pair #" << i << ": All you need is love!\n";
            } else {
                cout << "Pair #" << i << ": Love is not all you need!\n";
            }
        }
    }
    return 0;
}
