#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <functional>
using namespace std;

vector<string> valid_numbers;

bool is_multiple_of_22(const string &s) {
    if ((s.back() - '0') % 2 != 0) return false;
    int sum_odd = 0, sum_even = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (i % 2 == 0) sum_odd += (s[i] - '0');
        else sum_even += (s[i] - '0');
    }
    return (sum_odd - sum_even) % 11 == 0;
}

void generate_numbers(int n0, int n2) {
    string s;
    for (int i = 0; i < n2; ++i) s += '2';
    for (int i = 0; i < n0; ++i) s += '0';
    sort(s.begin(), s.end());
    do {
        if (is_multiple_of_22(s)) {
            valid_numbers.push_back(s);
        }
    } while (next_permutation(s.begin(), s.end()));
    sort(valid_numbers.begin(), valid_numbers.end());
    valid_numbers.erase(unique(valid_numbers.begin(), valid_numbers.end()), valid_numbers.end());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n0, n2;
    cin >> n0 >> n2;

    generate_numbers(n0, n2);

    if (valid_numbers.size() < 2) {
        cout << "-1\n";
    } else {
        cout << valid_numbers[valid_numbers.size() - 2] << '\n';
        cout << valid_numbers[1] << '\n';
    }

    return 0;
}
