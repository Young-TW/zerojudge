#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string trimLeadingZeros(const string& s) {
    size_t start = s.find_first_not_of('0');
    if (start == string::npos) return "0";
    return s.substr(start);
}

bool isGreaterOrEqual(const string& a, const string& b) {
    if (a.length() != b.length()) {
        return a.length() > b.length();
    }
    return a >= b;
}

string subtract(const string& a, const string& b) {
    string ra = a;
    string rb = b;
    reverse(ra.begin(), ra.end());
    reverse(rb.begin(), rb.end());
    
    string result = "";
    result.reserve(ra.length());
    int borrow = 0;
    for (size_t i = 0; i < ra.length(); ++i) {
        int digitA = ra[i] - '0';
        int digitB = (i < rb.length()) ? (rb[i] - '0') : 0;
        int diff = digitA - digitB - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result += (char)(diff + '0');
    }
    
    while (result.length() > 1 && result.back() == '0') {
        result.pop_back();
    }
    
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (cin >> n) {
        while (n--) {
            string a, b;
            if (!(cin >> a >> b)) break;
            a = trimLeadingZeros(a);
            b = trimLeadingZeros(b);
            
            if (isGreaterOrEqual(a, b)) {
                cout << subtract(a, b) << "\n";
            } else {
                cout << "-" << subtract(b, a) << "\n";
            }
        }
    }
    
    return 0;
}
