#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int digit_sum(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int compute_root(int num) {
    while (num >= 10) {
        num = digit_sum(num);
    }
    return num;
}

int compute_root_from_string(const string& s) {
    int sum = 0;
    for (char c : s) {
        sum += c - '0';
    }
    return compute_root(sum);
}

int main() {
    int N, R;
    while (cin >> N >> R) {
        string digits;
        cin >> digits;

        vector<string> results;
        for (int pos = 0; pos <= N - 1; ++pos) {
            for (int d = 0; d <= 9; ++d) {
                string candidate = digits.substr(0, pos) + char('0' + d) + digits.substr(pos);
                if (compute_root_from_string(candidate) == R) {
                    results.push_back(candidate);
                }
            }
        }

        sort(results.begin(), results.end());
        results.erase(unique(results.begin(), results.end()), results.end());

        if (results.size() >= 2) {
            auto min_it = min_element(results.begin(), results.end());
            auto max_it = max_element(results.begin(), results.end());
            results.erase(max_it);
            results.erase(min_it);
        }

        for (const string& res : results) {
            cout << res << endl;
        }
    }
    return 0;
}
