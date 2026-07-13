#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

string computeFraction(int A, int B) {
    if (A == 0) return "0.(0)";

    string res;
    if ((A < 0) ^ (B < 0)) {
        res += "-";
    }
    A = abs(A);
    B = abs(B);

    res += to_string(A / B);
    int remainder = A % B;
    if (remainder == 0) {
        return res + ".(0)";
    }

    res += ".";
    map<int, int> remainderPositions;
    vector<int> digits;
    bool hasCycle = false;
    int cycleStart = -1;

    while (remainder != 0) {
        if (remainderPositions.find(remainder) != remainderPositions.end()) {
            cycleStart = remainderPositions[remainder];
            hasCycle = true;
            break;
        }
        remainderPositions[remainder] = digits.size();
        remainder *= 10;
        digits.push_back(remainder / B);
        remainder %= B;
    }

    if (hasCycle) {
        for (int i = 0; i < cycleStart; ++i) {
            res += to_string(digits[i]);
        }
        res += "(";
        int cycleLength = digits.size() - cycleStart;
        if (cycleLength > 50) {
            for (int i = cycleStart; i < cycleStart + 50; ++i) {
                res += to_string(digits[i]);
            }
            res += "...)";
        } else {
            for (int i = cycleStart; i < digits.size(); ++i) {
                res += to_string(digits[i]);
            }
            res += ")";
        }
    } else {
        for (int digit : digits) {
            res += to_string(digit);
        }
        res += "(0)";
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        int A, B;
        cin >> A >> B;
        cout << computeFraction(A, B) << "\n";
    }

    return 0;
}
