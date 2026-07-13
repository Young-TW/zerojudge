#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

string multiply(const string &a, const string &b, int mod) {
    int len_a = a.size();
    int len_b = b.size();
    vector<int> res(len_a + len_b, 0);

    for (int i = 0; i < len_a; ++i) {
        for (int j = 0; j < len_b; ++j) {
            res[i + j + 1] += (a[i] - '0') * (b[j] - '0');
        }
    }

    for (int i = len_a + len_b - 1; i > 0; --i) {
        res[i - 1] += res[i] / 10;
        res[i] %= 10;
    }

    string result;
    for (int num : res) {
        if (!(result.empty() && num == 0)) {
            result.push_back(num + '0');
        }
    }
    if (result.empty()) result = "0";

    if (mod == 1) return "0";

    string mod_str;
    int mod_val = 0;
    int power = 1;
    for (int i = result.size() - 1; i >= 0 && mod_str.size() < mod; --i) {
        mod_val = (mod_val + (result[i] - '0') * power) % mod;
        power = (power * 10) % mod;
        mod_str.push_back(result[i]);
    }
    reverse(mod_str.begin(), mod_str.end());
    return to_string(mod_val);
}

int find_cycle_length(const string &n_str, int k) {
    if (k == 1) {
        int last_digit = n_str.back() - '0';
        if (last_digit == 0 || last_digit == 1 || last_digit == 5 || last_digit == 6) {
            return 1;
        } else if (last_digit == 4 || last_digit == 9) {
            return 2;
        } else {
            return 4;
        }
    }

    int mod = 1;
    for (int i = 0; i < k; ++i) {
        mod *= 10;
    }

    string current = "1";
    vector<int> visited(mod, -1);
    int pos = 0;

    while (true) {
        if (visited[stoi(current)] != -1) {
            return pos - visited[stoi(current)];
        }
        visited[stoi(current)] = pos;
        current = multiply(current, n_str, mod);
        pos++;

        if (current == "0") {
            return 1;
        }
    }

    return -1;
}

int main() {
    string n_str;
    int k;
    while (cin >> n_str >> k) {
        if (n_str == "0") {
            cout << 1 << endl;
            continue;
        }

        int mod = 1;
        for (int i = 0; i < k; ++i) {
            mod *= 10;
        }

        string n_mod = multiply(n_str, "1", mod);
        int n_val = stoi(n_mod);

        if (n_val == 0) {
            cout << 1 << endl;
            continue;
        }

        int cycle_length = find_cycle_length(n_str, k);
        cout << cycle_length << endl;
    }
    return 0;
}
