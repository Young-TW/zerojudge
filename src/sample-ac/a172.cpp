#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        // By Dilworth: min # of strictly-increasing subsequences to partition
        // = length of longest non-increasing (weakly decreasing) subsequence.
        // tail[i] = max ending value of a non-increasing subseq of length i+1.
        // tail is kept in non-increasing (descending) order.
        vector<int> tail;
        tail.reserve(n);
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            // find first element strictly less than x (descending partition)
            auto it = lower_bound(tail.begin(), tail.end(), x, greater_equal<int>());
            if (it == tail.end()) tail.push_back(x);
            else *it = x;
        }
        printf("%d\n", (int)tail.size());
    }
    return 0;
}
