#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long gcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long x;
    while (cin >> x) {
        if (x == 0) break;
        vector<long long> v;
        v.push_back(x);
        while (cin >> x && x != 0) {
            v.push_back(x);
        }
        
        sort(v.begin(), v.end());
        
        long long g = 0;
        for (size_t i = 1; i < v.size(); ++i) {
            long long diff = v[i] - v[i - 1];
            g = gcd(g, diff);
        }
        
        cout << g << "\n";
    }
    return 0;
}
