#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

vector<string> solve(int x, int y, int k) {
    if (k > max(x, y)) return {};
    int g = gcd(x, y);
    if (k % g != 0) return {};
    if (k == 0) return {}; // k>0 in problem, but handle gracefully
    if (k == x) return {"1 1"};
    if (k == y) return {"1 2"};

    vector<string> ops;
    int a = 0, b = 0;
    // The process is guaranteed to terminate within (x+y)*2 steps for valid inputs.
    int maxIter = (x + y) * 2 + 10;
    int iter = 0;

    while (true) {
        if (a == 0) {
            a = x;
            ops.push_back("1 1");
            if (a == k) break;
        }
        int pour = min(a, y - b);
        a -= pour;
        b += pour;
        ops.push_back("3 1 2");
        if (a == k || b == k) break;
        if (b == y) {
            b = 0;
            ops.push_back("2 2");
            if (a == k || b == k) break; // b becomes 0, only relevant if k==0
        }
        if (++iter > maxIter) return {}; // safety, should not happen
    }
    return ops;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<tuple<int, int, int>> cases;
    int x, y, k;
    while (cin >> x >> y >> k) {
        cases.emplace_back(x, y, k);
    }

    for (size_t i = 0; i < cases.size(); ++i) {
        tie(x, y, k) = cases[i];
        vector<string> ops = solve(x, y, k);
        if (ops.empty()) {
            cout << "0\n";
        } else {
            for (const string& op : ops) {
                cout << op << '\n';
            }
            cout << "0\n";
        }
        if (i + 1 < cases.size()) {
            cout << '\n';
        }
    }
    return 0;
}
