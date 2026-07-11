#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class BIT {
    vector<int> tree;
    int n;
public:
    BIT(int size) : n(size), tree(size + 1, 0) {}
    void update(int i, int delta) {
        for (; i <= n; i += i & -i)
            tree[i] += delta;
    }
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) continue;
        stringstream ss(line);
        vector<int> arr;
        int x;
        while (ss >> x) {
            arr.push_back(x);
        }
        if (arr.empty()) continue;
        int n = arr.size();
        BIT bit(n);
        long long total_complaints = 0;
        for (int val : arr) {
            total_complaints += (bit.query(n) - bit.query(val));
            bit.update(val, 1);
        }
        cout << total_complaints << "\n";
    }
    return 0;
}
