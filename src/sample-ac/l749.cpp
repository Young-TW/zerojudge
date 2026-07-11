#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string n;
    char s;
    int t, a;
    while (cin >> n >> s >> t >> a) {
        int len = n.size();
        vector<int> positions;
        for (int i = 1; i < len; ++i) {
            positions.push_back(i);
        }

        bool found = false;
        vector<int> current(t);
        do {
            for (int i = 0; i < t; ++i) {
                current[i] = positions[i];
            }
            sort(current.begin(), current.end());

            string expr = n;
            int offset = 0;
            for (int pos : current) {
                expr.insert(pos + offset, 1, s);
                offset++;
            }

            vector<int> nums;
            vector<char> ops;
            int num = 0;
            for (char c : expr) {
                if (isdigit(c)) {
                    num = num * 10 + (c - '0');
                } else {
                    nums.push_back(num);
                    ops.push_back(c);
                    num = 0;
                }
            }
            nums.push_back(num);

            int result = nums[0];
            for (int i = 0; i < ops.size(); ++i) {
                if (ops[i] == '+') {
                    result += nums[i+1];
                } else if (ops[i] == '-') {
                    result -= nums[i+1];
                } else if (ops[i] == '*') {
                    result *= nums[i+1];
                } else if (ops[i] == '/') {
                    result /= nums[i+1];
                }
            }

            if (result == a) {
                cout << expr << "=" << a << endl;
                found = true;
                break;
            }
        } while (next_permutation(positions.begin(), positions.end()));

        if (!found) {
            cout << "No solution" << endl;
        }
    }
    return 0;
}
