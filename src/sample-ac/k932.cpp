#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long a, b;
    while (cin >> a >> b) {
        vector<long long> cf;
        while (b != 0) {
            cf.push_back(a / b);
            long long r = a % b;
            a = b;
            b = r;
        }
        
        cout << "[" << cf[0];
        if (cf.size() > 1) {
            cout << ";";
            for (size_t i = 1; i < cf.size(); ++i) {
                if (i > 1) cout << ",";
                cout << cf[i];
            }
        }
        cout << "]\n";
    }
    
    return 0;
}
