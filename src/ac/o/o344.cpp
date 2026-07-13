#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (!(cin >> t)) return 0;
    
    while (t--) {
        int n;
        cin >> n;
        vector<long long> w(n + 2);
        vector<long long> prefix(n + 2, 0);
        for (int i = 1; i <= n; ++i) {
            cin >> w[i];
            prefix[i] = prefix[i - 1] + w[i];
        }
        w[0] = -1;
        w[n + 1] = -1;
        
        vector<int> s;
        s.reserve(n + 2);
        s.push_back(0);
        
        long long max_ans = 0;
        for (int i = 1; i <= n + 1; ++i) {
            while (w[s.back()] > w[i]) {
                int top = s.back();
                s.pop_back();
                long long sum = prefix[i - 1] - prefix[s.back()];
                long long val = sum * w[top];
                if (val > max_ans) {
                    max_ans = val;
                }
            }
            s.push_back(i);
        }
        
        cout << max_ans << "\n";
    }
    
    return 0;
}
