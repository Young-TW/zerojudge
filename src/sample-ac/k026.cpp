#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        
        if (n % 2 == 1) {
            cout << arr[n / 2] << "\n";
        } else {
            cout << (arr[n / 2 - 1] + arr[n / 2]) / 2 << "\n";
        }
    }
    
    return 0;
}
