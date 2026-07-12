#include <iostream>
#include <vector>

using namespace std;

int fib(int n) {
    if (n < 2) return 1;
    return fib(n - 1) + fib(n - 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n != 0) {
        cout << "f(" << n << ") \n";
        
        vector<int> curr = {n};
        while (true) {
            bool has_ge2 = false;
            vector<int> next;
            for (int x : curr) {
                if (x >= 2) {
                    has_ge2 = true;
                    next.push_back(x - 1);
                    next.push_back(x - 2);
                } else {
                    next.push_back(x);
                }
            }
            
            if (!has_ge2) break;
            
            for (int x : next) {
                cout << "f(" << x << ") ";
            }
            cout << "\n";
            
            curr = next;
        }
        
        cout << "f(" << n << ") = " << fib(n) << "\n\n";
    }
    
    return 0;
}
