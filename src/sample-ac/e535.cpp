#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        while (N--) {
            string M;
            cin >> M;
            
            int k;
            cin >> k;
            vector<int> S(k);
            for (int i = 0; i < k; ++i) {
                cin >> S[i];
            }
            
            bool wonderful = true;
            for (int d : S) {
                if (d == 0) continue; 
                int rem = 0;
                for (char c : M) {
                    rem = (rem * 10 + (c - '0')) % d;
                }
                if (rem != 0) {
                    wonderful = false;
                    break;
                }
            }
            
            if (wonderful) {
                cout << M << " - Wonderful.\n";
            } else {
                cout << M << " - Simple.\n";
            }
        }
    }
    
    return 0;
}
