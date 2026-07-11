#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    int case_num = 1;
    
    while (cin >> N) {
        vector<long long> S(N);
        for (int i = 0; i < N; ++i) {
            cin >> S[i];
        }
        
        long long max_product = 0;
        for (int i = 0; i < N; ++i) {
            long long current_product = 1;
            for (int j = i; j < N; ++j) {
                current_product *= S[j];
                if (current_product > max_product) {
                    max_product = current_product;
                }
            }
        }
        
        cout << "Case #" << case_num << ": The maximum product is " << max_product << ".\n\n";
        case_num++;
    }
    
    return 0;
}
