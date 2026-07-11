#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int arr[4];
    while (cin >> arr[0] >> arr[1] >> arr[2] >> arr[3]) {
        sort(arr, arr + 4);
        bool is_pony = true;
        for (int i = 0; i < 3; ++i) {
            if (arr[i] == arr[i + 1]) {
                is_pony = false;
                break;
            }
        }
        if (is_pony) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
