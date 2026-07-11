#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        for (int i = 1; i <= T; ++i) {
            int arr[3];
            cin >> arr[0] >> arr[1] >> arr[2];
            sort(arr, arr + 3);
            cout << "Case " << i << ": " << arr[1] << "\n";
        }
    }
    
    return 0;
}
