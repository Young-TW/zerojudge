#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int getGCD(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

vector<pair<int, int>> factorize(int n) {
    vector<pair<int, int>> factors;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            int count = 0;
            while (n % i == 0) {
                n /= i;
                count++;
            }
            factors.push_back(make_pair(i, count));
        }
    }
    if (n > 1) {
        factors.push_back(make_pair(n, 1));
    }
    return factors;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    while (n--) {
        int a, b;
        cin >> a >> b;
        
        vector<pair<int, int>> factors = factorize(a);
        
        for (size_t i = 0; i < factors.size(); ++i) {
            if (i > 0) cout << "*";
            cout << factors[i].first;
            if (factors[i].second > 1) {
                cout << "^" << factors[i].second;
            }
        }
        
        int gcd = getGCD(a, b);
        cout << " , " << gcd << " , " << (isPrime(gcd) ? "Y" : "N") << "\n";
    }
    
    return 0;
}
