#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n, m;
    while (cin >> n >> m) {
        vector<long long> seq;
        seq.push_back(n);
        long long curr = n;
        bool valid = true;
        
        while (curr != 1) {
            if (m <= 1) {
                valid = false;
                break;
            }
            if (curr % m != 0) {
                valid = false;
                break;
            }
            long long next = curr / m;
            if (next >= curr) {
                valid = false;
                break;
            }
            curr = next;
            seq.push_back(curr);
        }
        
        if (valid) {
            for (int i = 0; i < (int)seq.size(); ++i) {
                if (i > 0) cout << " ";
                cout << seq[i];
            }
            cout << "\n";
        } else {
            cout << "Boring!\n";
        }
    }
    
    return 0;
}
