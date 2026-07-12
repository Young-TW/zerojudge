#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string subtractStrings(string a, string b) {
    int i = a.size() - 1, j = b.size() - 1;
    int carry = 0;
    string result;
    while (i >= 0 || j >= 0 || carry) {
        int digitA = (i >= 0) ? (a[i--] - '0') : 0;
        int digitB = (j >= 0) ? (b[j--] - '0') : 0;
        int diff = digitA - digitB - carry;
        if (diff < 0) {
            diff += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        result.push_back(diff + '0');
    }
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }
    reverse(result.begin(), result.end());
    return result;
}

bool isLessOrEqual(string a, string b) {
    if (a.size() != b.size()) {
        return a.size() < b.size();
    }
    return a <= b;
}

string divideLargeNumbers(string xi, string eta) {
    if (eta == "1") {
        return xi;
    }
    string quotient = "0";
    string current;
    for (char c : xi) {
        current.push_back(c);
        if (current.size() < eta.size() || (current.size() == eta.size() && current < eta)) {
            quotient.push_back('0');
            continue;
        }
        int count = 0;
        while (isLessOrEqual(eta, current)) {
            current = subtractStrings(current, eta);
            count++;
        }
        quotient.push_back(count + '0');
    }
    size_t nonZeroPos = quotient.find_first_not_of('0');
    if (nonZeroPos != string::npos) {
        quotient = quotient.substr(nonZeroPos);
    } else {
        quotient = "0";
    }
    return quotient;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    while (cin >> T) {
        while (T--) {
            string xi, eta;
            cin >> xi >> eta;
            string result = divideLargeNumbers(xi, eta);
            cout << result << '\n';
        }
    }
    return 0;
}
