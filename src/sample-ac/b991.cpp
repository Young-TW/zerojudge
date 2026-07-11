#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

unordered_map<long long, int> memo[3];

int friunlde(long long n, int k) {
    if (n == 0) return 0;
    if (memo[k].count(n)) return memo[k][n];

    if (n % 2 == 1) {
        int val = friunlde(n - 1, k);
        memo[k][n] = (val == 0) ? 1 : 0;
    } else {
        int val1 = friunlde(n - 1, k);
        int val2 = friunlde(n / 2, k) * (k % 2);
        vector<int> s = {val1, val2};
        sort(s.begin(), s.end());
        s.erase(unique(s.begin(), s.end()), s.end());
        int mex = 0;
        while (find(s.begin(), s.end(), mex) != s.end()) {
            mex++;
        }
        memo[k][n] = mex;
    }
    return memo[k][n];
}

int main() {
    long long n;
    int k;
    while (cin >> n >> k) {
        cout << friunlde(n, k) << endl;
    }
    return 0;
}
