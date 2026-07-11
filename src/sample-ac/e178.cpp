#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    long long k;
    while (cin >> n >> k) {
        if (n == 0) {
            cout << 0 << "\n";
            continue;
        }
        
        vector<int> cards(n);
        long long sum = 0;
        vector<int> negs;
        int minAbs = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            cin >> cards[i];
            sum += cards[i];
            int a = cards[i] < 0 ? -cards[i] : cards[i];
            if (cards[i] < 0) negs.push_back(a);
            if (a < minAbs) minAbs = a;
        }
        
        int c = (int)negs.size();
        long long result;
        
        if (k <= c) {
            sort(negs.rbegin(), negs.rend());
            long long gain = 0;
            for (int i = 0; i < (int)k; i++) {
                gain += 2LL * negs[i];
            }
            result = sum + gain;
        } else {
            long long rem = k - c;
            long long totalAbs = 0;
            for (int i = 0; i < n; i++) {
                int a = cards[i] < 0 ? -cards[i] : cards[i];
                totalAbs += a;
            }
            if (rem % 2 == 0) {
                result = totalAbs;
            } else {
                result = totalAbs - 2LL * minAbs;
            }
        }
        
        cout << result << "\n";
    }
    
    return 0;
}
