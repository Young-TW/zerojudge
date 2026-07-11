#include <iostream>
#include <string>

using namespace std;

size_t gcd(size_t a, size_t b) {
    while (b) {
        size_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

bool check(const string& s, const string& g) {
    if (s.length() % g.length() != 0) return false;
    for (size_t i = 0; i < s.length(); ++i) {
        if (s[i] != g[i % g.length()]) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s1, s2;
    while (cin >> s1 >> s2) {
        size_t l1 = s1.length();
        size_t l2 = s2.length();
        size_t l = gcd(l1, l2);
        string g = s1.substr(0, l);
        
        if (check(s1, g) && check(s2, g)) {
            cout << g << "\n";
        } else {
            cout << "= =" << "\n";
        }
    }
    
    return 0;
}
