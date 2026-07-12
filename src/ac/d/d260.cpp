#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        while (T--) {
            long long arr[4];
            cin >> arr[0] >> arr[1] >> arr[2] >> arr[3];
            sort(arr, arr + 4);
            
            if (arr[0] == arr[1] && arr[1] == arr[2] && arr[2] == arr[3]) {
                cout << "square\n";
            } else if (arr[0] == arr[1] && arr[2] == arr[3]) {
                cout << "rectangle\n";
            } else if (arr[0] + arr[1] + arr[2] > arr[3]) {
                cout << "quadrangle\n";
            } else {
                cout << "banana\n";
            }
        }
    }
    
    return 0;
}
