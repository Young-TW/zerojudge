#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    int num_primes = 25;
    
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            string num;
            cin >> num;
            int rems[25] = {0};
            
            for (char c : num) {
                int digit = c - '0';
                for (int j = 0; j < num_primes; ++j) {
                    rems[j] = (rems[j] * 10 + digit) % primes[j];
                }
            }
            
            vector<int> ans;
            for (int j = 0; j < num_primes; ++j) {
                if (rems[j] == 0) {
                    ans.push_back(primes[j]);
                }
            }
            
            if (ans.empty()) {
                cout << "Terrible Silence...\n";
            } else {
                for (size_t j = 0; j < ans.size(); ++j) {
                    if (j > 0) cout << " ";
                    cout << ans[j];
                }
                cout << "\n";
            }
        }
    }
    
    return 0;
}
