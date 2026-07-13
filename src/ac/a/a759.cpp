#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long B;
    while (cin >> B) {
        int D;
        if (!(cin >> D)) break;
        
        int maxS = 0;
        int count = 0;
        
        for (int i = 0; i < D; ++i) {
            int N;
            string A;
            if (!(cin >> N >> A)) break;
            
            long long numA = 0;
            bool valid = true;
            
            for (char c : A) {
                int digit;
                if (c >= '0' && c <= '9') {
                    digit = c - '0';
                } else if (c >= 'A' && c <= 'F') {
                    digit = c - 'A' + 10;
                } else if (c >= 'a' && c <= 'f') {
                    digit = c - 'a' + 10;
                } else {
                    valid = false;
                    break;
                }
                
                numA = numA * N + digit;
                if (numA >= B) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                long long sum = numA + B;
                int S = 0;
                while (sum > 0) {
                    S += sum & 1;
                    sum >>= 1;
                }
                
                if (S > maxS) {
                    maxS = S;
                    count = 1;
                } else if (S == maxS) {
                    count++;
                }
            }
        }
        
        cout << maxS << " " << count << "\n";
    }
    
    return 0;
}
