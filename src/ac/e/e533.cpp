#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    if (cin >> n) {
        cout << "Lumberjacks:\n";
        while (n--) {
            vector<int> v(10);
            for (int i = 0; i < 10; ++i) {
                cin >> v[i];
            }
            bool inc = true, dec = true;
            for (int i = 0; i < 9; ++i) {
                if (v[i] > v[i + 1]) {
                    inc = false;
                }
                if (v[i] < v[i + 1]) {
                    dec = false;
                }
            }
            if (inc || dec) {
                cout << "Ordered\n";
            } else {
                cout << "Unordered\n";
            }
        }
    }
    
    return 0;
}
