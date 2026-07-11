#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        sort(arr.begin(), arr.end());
        for (int i = 0; i < n; ++i) {
            cout << arr[i];
            if (i < n - 1) {
                cout << ' ';
            }
        }
        cout << '\n';
    }
    
    return 0;
}
