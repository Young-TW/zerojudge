#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        
        vector<int> class1, class2;
        for (int i = 0; i < n; i++) {
            if (a[i] > b[i]) {
                class1.push_back(i + 1);
            } else {
                class2.push_back(i + 1);
            }
        }
        
        if (class1.empty()) {
            cout << -1 << "\n";
        } else {
            for (size_t i = 0; i < class1.size(); i++) {
                if (i > 0) cout << " ";
                cout << class1[i];
            }
            cout << "\n";
        }
        
        if (class2.empty()) {
            cout << -1 << "\n";
        } else {
            for (size_t i = 0; i < class2.size(); i++) {
                if (i > 0) cout << " ";
                cout << class2[i];
            }
            cout << "\n";
        }
    }
    
    return 0;
}
