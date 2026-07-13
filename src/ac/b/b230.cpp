#include <iostream>
#include <vector>

using namespace std;

bool is_idoneal(int N) {
    for (int a = 1; ; ++a) {
        int b_min = a + 1;
        if (a * b_min + (b_min + 1) * (a + b_min) > N) break;
        for (int b = a + 1; ; ++b) {
            int ab = a * b;
            int sum_ab = a + b;
            if (ab + (b + 1) * sum_ab > N) break;
            int rem = N - ab;
            if (rem % sum_ab == 0) {
                int c = rem / sum_ab;
                if (c > b) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> idoneal_nums;
    int N = 1;
    while (idoneal_nums.size() < 65) {
        if (is_idoneal(N)) {
            idoneal_nums.push_back(N);
        }
        N++;
    }
    
    int k;
    bool first = true;
    while (cin >> k) {
        if (!first) {
            cout << "\n";
        }
        cout << idoneal_nums[k - 1] << "\n";
        first = false;
    }
    return 0;
}
