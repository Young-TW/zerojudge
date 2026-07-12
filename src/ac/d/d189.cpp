#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        int total = n;
        int empty = n;
        while (empty >= 3 || empty == 2) {
            if (empty == 2) {
                empty++; // 借一個空罐
            }
            int new_cola = empty / 3;
            total += new_cola;
            empty = empty % 3 + new_cola;
        }
        cout << total << "\n";
    }
    
    return 0;
}
