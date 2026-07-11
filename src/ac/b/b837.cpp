#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> fibs;
    fibs.push_back(0);
    fibs.push_back(1);
    while (true) {
        int next = fibs[fibs.size() - 1] + fibs[fibs.size() - 2];
        if (next > 1000000) break;
        fibs.push_back(next);
    }
    
    int t;
    bool first_case = true;
    while (cin >> t) {
        for (int i = 0; i < t; ++i) {
            int A, B;
            cin >> A >> B;
            int L = min(A, B);
            int R = max(A, B);
            
            if (!first_case) {
                cout << "------\n";
            }
            first_case = false;
            
            int count = 0;
            for (int f : fibs) {
                if (f >= L && f <= R) {
                    cout << f << "\n";
                    count++;
                }
            }
            
            if (count == 0) {
                cout << "0\n";
            } else {
                cout << count << "\n";
            }
        }
    }
    
    return 0;
}
