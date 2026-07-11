#include <iostream>
#include <bitset>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        while (N--) {
            unsigned int a, b;
            char op;
            cin >> hex >> a >> op >> b;
            
            unsigned int res;
            if (op == '+') {
                res = a + b;
            } else {
                res = a - b;
            }
            
            cout << bitset<13>(a) << " " << op << " " << bitset<13>(b) << " = " << res << "\n";
        }
    }
    
    return 0;
}
